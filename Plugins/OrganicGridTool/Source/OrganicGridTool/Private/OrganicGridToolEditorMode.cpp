// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrganicGridToolEditorMode.h"
#include "OrganicGridToolEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "OrganicGridToolEditorModeCommands.h"

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Editor.h"
#include "Runtime/Datasmith/CADKernel/Public/CADKernel/Core/Types.h"
#include "Shader/ShaderTypes.h"
#include "Tools/OrganicGridToolSimpleTool.h"
#include "Tools/OrganicGridToolInteractiveTool.h"

// step 2: register a ToolBuilder in FOrganicGridToolEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "OrganicGridToolEditorMode"

const FEditorModeID UOrganicGridToolEditorMode::EM_OrganicGridToolEditorModeId = TEXT("EM_OrganicGridToolEditorMode");

FString UOrganicGridToolEditorMode::SimpleToolName = TEXT("OrganicGridTool_ActorInfoTool");
FString UOrganicGridToolEditorMode::InteractiveToolName = TEXT("OrganicGridTool_MeasureDistanceTool");

///-///////////////////////////////////////////////////////////////////////////////////////////
///
UOrganicGridToolEditorMode::UOrganicGridToolEditorMode()
{
	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UOrganicGridToolEditorMode::EM_OrganicGridToolEditorModeId,
		LOCTEXT("ModeName", "OrganicGridTool"),
		FSlateIcon(),
		true);
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
UOrganicGridToolEditorMode::~UOrganicGridToolEditorMode()
{
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
void UOrganicGridToolEditorMode::ActorSelectionChangeNotify()
{
	if (GetToolManager()->GetActiveTool(EToolSide::Left) == nullptr)
	{
		if (GEditor)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();
		}
	}
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
void UOrganicGridToolEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FOrganicGridToolEditorModeCommands& SampleToolCommands = FOrganicGridToolEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UOrganicGridToolSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UOrganicGridToolInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
void UOrganicGridToolEditorMode::Exit()
{
	Super::Exit();
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
void UOrganicGridToolEditorMode::ModeTick(float DeltaTime)
{
	Super::ModeTick(DeltaTime);
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
void UOrganicGridToolEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FOrganicGridToolEditorModeToolkit);
}

///-///////////////////////////////////////////////////////////////////////////////////////////
///
TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UOrganicGridToolEditorMode::GetModeCommands() const
{
	return FOrganicGridToolEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
