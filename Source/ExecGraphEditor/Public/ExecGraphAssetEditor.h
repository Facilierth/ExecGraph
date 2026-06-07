// Copyright (c) 2026, Jaroszyńska

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UExecGraphAsset;
class SGraphEditor;

class FExecGraphAssetEditor : public FAssetEditorToolkit, public FGCObject
{
public:
	FExecGraphAssetEditor();
	virtual ~FExecGraphAssetEditor();

	// open the editor window panel
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UExecGraphAsset* InAsset);

	// IToolkit/FAssetEditorToolkit
	virtual FName GetToolkitFName() const override { return FName("ExecGraphEditor"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("ExecGraphEditor", "AppLabel", "Exec Graph Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("ExecGraphEditor"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f); }

	// prevents edited asset from being garbage collected mid-edit
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override { return TEXT("FExecGraphAssetEditor"); }

private:
	// property sidebar tab
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	// whenever sb clicks a node on the canvas
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& NewSelection);

	void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);

	TSharedPtr<IDetailsView> DetailsWidget;
	UExecGraphAsset* EditingAsset = nullptr;
	TSharedPtr<SGraphEditor> GraphEditorWidget;
};