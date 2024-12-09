// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrganicGridToolModule.h"
#include "OrganicGridToolEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "OrganicGridToolModule"

void FOrganicGridToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FOrganicGridToolEditorModeCommands::Register();
}

void FOrganicGridToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FOrganicGridToolEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOrganicGridToolModule, OrganicGridToolEditorMode)