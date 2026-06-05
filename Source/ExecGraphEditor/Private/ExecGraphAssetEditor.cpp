// Copyright (c) 2026, Jaroszyńska

#include "ExecGraphAssetEditor.h"
#include "ExecGraphAsset.h"
#include "EdGraph_ExecGraph.h"
#include "EdGraphSchema_ExecGraph.h"
#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"

FExecGraphAssetEditor::FExecGraphAssetEditor() {}
FExecGraphAssetEditor::~FExecGraphAssetEditor() {}

void FExecGraphAssetEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UExecGraphAsset* InAsset)
{
    EditingAsset = InAsset;

    // fresh edgraph canvas container if one doesn't exist yet
    if (!EditingAsset->EdGraph)
    {
        UEdGraph_ExecGraph* NewGraph = NewObject<UEdGraph_ExecGraph>(EditingAsset, UEdGraph_ExecGraph::StaticClass(), NAME_None, RF_Transactional);
        NewGraph->Schema = UEdGraphSchema_ExecGraph::StaticClass();
        NewGraph->ExecGraphAsset = EditingAsset;
        EditingAsset->EdGraph = NewGraph;
    }

    SGraphEditor::FGraphEditorEvents Events;
    
    GraphEditorWidget = SNew(SGraphEditor)
        .AdditionalCommands(GetToolkitCommands())
        .GraphToEdit(EditingAsset->EdGraph)
        .GraphEvents(Events);
    

    const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_ExecGraphEditor_Layout_v1")
        ->AddArea(
            FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
            ->Split(
                FTabManager::NewStack()->AddTab("ExecGraphCanvasTab", ETabState::OpenedTab)
            )
        );

    InitAssetEditor(Mode, InitToolkitHost, FName("ExecGraphEditorApp"), Layout, true, true, InAsset);
}

void FExecGraphAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    InTabManager->RegisterTabSpawner("ExecGraphCanvasTab", FOnSpawnTab::CreateRaw(this, &FExecGraphAssetEditor::SpawnTab_GraphCanvas))
        .SetDisplayName(NSLOCTEXT("ExecGraphEditor", "CanvasTab", "Viewport Canvas"));
}

void FExecGraphAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
    InTabManager->UnregisterTabSpawner("ExecGraphCanvasTab");
}

TSharedRef<SDockTab> FExecGraphAssetEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(NSLOCTEXT("ExecGraphEditor", "CanvasTabTitle", "Exec Graph Canvas"))
        [
            GraphEditorWidget.ToSharedRef()
        ];
}

void FExecGraphAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(EditingAsset);
}