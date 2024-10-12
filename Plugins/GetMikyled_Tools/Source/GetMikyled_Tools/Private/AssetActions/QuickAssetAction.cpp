// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetActions/QuickAssetAction.h"

#include "AssetToolsModule.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetViewUtils.h"

#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"

// Duplicate Assets
void UQuickAssetAction::DuplicateAssets(int32 NumOfDuplicates)
{
	// Check if the input is a valid number
	if (NumOfDuplicates <= 0)
	{
		ShowMsgDialog(EAppMsgType::Ok, TEXT("Please enter a valid number."));
		return;
	}

	// Get the selected assets
	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 Counter = 0;

	// Create duplicates equal to NumOfDuplicates for every selected assets
	for (const FAssetData& SelectedAssetData : SelectedAssetsData)
	{
		for (int32 i = 0; i < NumOfDuplicates; i++)
		{
			// Obtain necessary information to duplicate asset
			const FString SourceAssetPath = SelectedAssetData.GetObjectPathString();
			const FString NewAssetName = SelectedAssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i+1);
			const FString NewPathName = FPaths::Combine(SelectedAssetData.PackagePath.ToString(), NewAssetName);

			// Duplicate and save the asset
			if (UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				UEditorAssetLibrary::SaveAsset(NewPathName, false);
				Counter++;
			}
		}
	}

	// If the counter is greater than 0, output a notification indicating success
	if (Counter > 0)
	{
		ShowNotifyInfo(TEXT("Successfully duplicated " + FString::FromInt(Counter) + " files."));
	}
}

void UQuickAssetAction::AddPrefixes()
{
	// Get the objects of the selected assets
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;

	// Loop through all the selected objects
	for (UObject* SelectedObject : SelectedObjects)
	{
		// Check for validity
		if (SelectedObject)
		{
			FString* PrefixFound = PrefixMap.Find(SelectedObject->GetClass());

			// Check if a prefix was found for the object
			if (PrefixFound || PrefixFound->IsEmpty() == false)
			{
				FString OldName = SelectedObject->GetName();

				// Check if the file already has the prefix
				if (OldName.StartsWith(*PrefixFound) == false)
				{
					// Check for custom names
					if (SelectedObject->IsA<UMaterialInstance>())
					{
						OldName.RemoveFromStart("M_");
						OldName.RemoveFromEnd("_Inst");
					}
					
					// Rename the file with the prefix
					const FString NewNameWithPrefix = *PrefixFound + OldName;
					UEditorUtilityLibrary::RenameAsset(SelectedObject, NewNameWithPrefix);
				}
				else
				{
					// If the file already has the prefix, log to notify user
					PrintLog(OldName + TEXT(" already contains the correct prefix."));
				}
				
				Counter++;
			}
			else
			{
				// If a prefix was not found, log to notify user
				PrintLog(TEXT("Failed to find prefix for class " + SelectedObject->GetClass()->GetName()));
			}
		}
	}

	// If the counter is greater than 0, output a notification indicating success
	if (Counter > 0)
	{
		ShowNotifyInfo(TEXT("Successfully added prefixes to " + FString::FromInt(Counter) + " files."));
	}
}

void UQuickAssetAction::RemoveUnusedAssets()
{
	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<FAssetData> UnusedAssetsData;
	
	for (FAssetData AssetData : SelectedAssetsData)
	{
		// Get references
		const FString AssetPath = AssetData.GetObjectPathString();
		TArray<FString> AssetReferences = UEditorAssetLibrary::FindPackageReferencersForAsset(AssetPath);

		// If asset has no references, add to UnusedAssets array
		if (AssetReferences.Num() == 0)
		{
			UnusedAssetsData.Add(AssetData);
		}
	}

	// If no unused assets found, display message and return
	if (UnusedAssetsData.Num() == 0)
	{
		ShowMsgDialog(EAppMsgType::Ok, TEXT("No unused assets found"), false);
		return;
	}

	const int32 NumOfDeletedAssets = ObjectTools::DeleteAssets(UnusedAssetsData);
	if (NumOfDeletedAssets > 0)
	{
		ShowNotifyInfo(TEXT("Successfully deleted " + FString::FromInt(NumOfDeletedAssets) + " unused assets."));
	}
}

void UQuickAssetAction::FixUpRedirectors()
{
	// Get asset registry module
	IAssetRegistry& AssetRegistry = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	// Create filter
	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Emplace("/Game");
	Filter.ClassPaths.Add(UObjectRedirector::StaticClass()->GetClassPathName());

	// Get assets in asset registry
	TArray<FAssetData> Assets;
	AssetRegistry.GetAssets(Filter, Assets);

	// Return if there are no assets
	if (Assets.Num() == 0)
	{
		return;
	}

	// Get object paths from assets
	TArray<FString> ObjectPaths;
	for (const FAssetData& Asset : Assets)
	{
		ObjectPaths.Add(Asset.GetObjectPathString());
	}

	TArray<UObject*> Objects;
	const bool bAllowedToPromptToLoadAssets = true;
	const bool bLoadRedirects = true;

	AssetViewUtils::FLoadAssetsSettings Settings;
	Settings.bFollowRedirectors = false;
	Settings.bAllowCancel = true;

	AssetViewUtils::ELoadAssetsResult Result = LoadAssetsIfNeeded(ObjectPaths, Objects, Settings);
	if (Result != AssetViewUtils::ELoadAssetsResult::Cancelled)
	{
		// Get redirecots of the objects
		TArray<UObjectRedirector*>	Redirectors;
		for (UObject* Object : Objects)
		{
			Redirectors.Add(CastChecked<UObjectRedirector>(Object));
		}

		// Load the asset tools module
		FAssetToolsModule& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
		AssetTools.Get().FixupReferencers(Redirectors);
	}
}


