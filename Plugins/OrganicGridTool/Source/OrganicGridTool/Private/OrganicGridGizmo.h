#pragma once

void DrawOrganicGridGizmo()
{
	DrawDebugLine(GEditor->GetEditorWorldContext().World(), FVector(0,0,0), FVector(100,100,0), FColor::Red);
}