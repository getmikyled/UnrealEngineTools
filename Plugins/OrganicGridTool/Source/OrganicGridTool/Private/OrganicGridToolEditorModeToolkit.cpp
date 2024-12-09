// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrganicGridToolEditorModeToolkit.h"
#include "OrganicGridToolEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "OrganicGridToolEditorModeToolkit"

FOrganicGridToolEditorModeToolkit::FOrganicGridToolEditorModeToolkit()
{
}

void FOrganicGridToolEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FOrganicGridToolEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FOrganicGridToolEditorModeToolkit::GetToolkitFName() const
{
	return FName("OrganicGridToolEditorMode");
}

FText FOrganicGridToolEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "OrganicGridToolEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
