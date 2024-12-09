// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrganicGridToolEditorModeCommands.h"
#include "OrganicGridToolEditorMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "OrganicGridToolEditorModeCommands"

FOrganicGridToolEditorModeCommands::FOrganicGridToolEditorModeCommands()
	: TCommands<FOrganicGridToolEditorModeCommands>("OrganicGridToolEditorMode",
		NSLOCTEXT("OrganicGridToolEditorMode", "OrganicGridToolEditorModeCommands", "OrganicGridTool Editor Mode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FOrganicGridToolEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(SimpleTool, "Show Actor Info", "Opens message box with info about a clicked actor", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(SimpleTool);

	UI_COMMAND(InteractiveTool, "Measure Distance", "Measures distance between 2 points (click to set origin, shift-click to set end point)", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(InteractiveTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FOrganicGridToolEditorModeCommands::GetCommands()
{
	return FOrganicGridToolEditorModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE
