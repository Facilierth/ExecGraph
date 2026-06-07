// Copyright (c) 2026, Jaroszyńska

#include "ExecGraphAssetEditor.h"

#include "EdGraphNode_ExecGraph.h"
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
    
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bAllowSearch = false;
    DetailsViewArgs.bHideSelectionTip = true;
    DetailsWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

    // fresh edgraph canvas container if one doesn't exist yet
    if (!EditingAsset->EdGraph)
    {
        UEdGraph_ExecGraph* NewGraph = NewObject<UEdGraph_ExecGraph>(EditingAsset, UEdGraph_ExecGraph::StaticClass(), NAME_None, RF_Transactional);
        NewGraph->Schema = UEdGraphSchema_ExecGraph::StaticClass();
        NewGraph->ExecGraphAsset = EditingAsset;
        EditingAsset->EdGraph = NewGraph;
    }

    SGraphEditor::FGraphEditorEvents Events;
    Events.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FExecGraphAssetEditor::OnGraphSelectionChanged);
    
    GraphEditorWidget = SNew(SGraphEditor)
        .AdditionalCommands(GetToolkitCommands())
        .GraphToEdit(EditingAsset->EdGraph)
        .GraphEvents(Events);

    // canvas on the Left (0.75), property sidebar on the Right (0.25)
    const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_ExecGraphEditor_Layout_v2")
         ->AddArea(
             FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
             ->Split(
                 FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
                 ->Split(FTabManager::NewStack()->AddTab("ExecGraphCanvasTab", ETabState::OpenedTab))->SetSizeCoefficient(0.75f)
                 ->Split(FTabManager::NewStack()->AddTab("ExecGraphDetailsTab", ETabState::OpenedTab))->SetSizeCoefficient(0.25f)
             )
         );

    InitAssetEditor(Mode, InitToolkitHost, FName("ExecGraphEditorApp"), Layout, true, true, InAsset);
}

void FExecGraphAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    InTabManager->RegisterTabSpawner("ExecGraphCanvasTab",
        FOnSpawnTab::CreateRaw(this, &FExecGraphAssetEditor::SpawnTab_GraphCanvas));
    InTabManager->RegisterTabSpawner("ExecGraphDetailsTab", 
        FOnSpawnTab::CreateRaw(this, &FExecGraphAssetEditor::SpawnTab_Details));
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


TSharedRef<SDockTab> FExecGraphAssetEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab).Label(NSLOCTEXT("ExecGraphEditor", "DetailsTabTitle", "Details"))[DetailsWidget.ToSharedRef()];
}

void FExecGraphAssetEditor::OnGraphSelectionChanged(const FGraphPanelSelectionSet& NewSelection)
{
    if (NewSelection.Num() == 1)
    {
        // Get the single selected visual node box
        for (UObject* Obj : NewSelection)
        {
            if (UEdGraphNode_ExecGraph* VisualNode = Cast<UEdGraphNode_ExecGraph>(Obj))
            {
                if (DetailsWidget.IsValid())
                {
                    DetailsWidget->SetObject(VisualNode->RuntimeNode);
                }
                return;
            }
        }
    }
    
    // if sb clicks empty space, lets clear it
    if (DetailsWidget.IsValid()) DetailsWidget->SetObject(nullptr);
}