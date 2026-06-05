// Copyright (c) 2026, Jaroszyńska


#include "AssetActions_ExecGraph.h"
#include "ExecGraphAsset.h"

FText FAssetTypeActions_ExecGraph::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExecGraph", "Exec Graph");
}

FColor FAssetTypeActions_ExecGraph::GetTypeColor() const
{
	return FColor(122, 0, 204); // nice purple, kind of like my hair
}

UClass* FAssetTypeActions_ExecGraph::GetSupportedClass() const
{
	return UExecGraphAsset::StaticClass();
}

uint32 FAssetTypeActions_ExecGraph::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FAssetTypeActions_ExecGraph::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}