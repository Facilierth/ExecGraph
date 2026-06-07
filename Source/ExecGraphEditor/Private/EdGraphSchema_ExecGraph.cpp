// Copyright (c) 2026, Jaroszyńska

#include "EdGraphSchema_ExecGraph.h"

#include "EdGraphNode_ExecGraph.h"
#include "ExecGraphConnectionDrawingPolicy.h"
#include "Layout/SlateRect.h"
#include "ExecGraphEditor.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphSchema.h"


struct FExecGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
    UClass* RuntimeNodeClass;

    FExecGraphSchemaAction_NewNode(FText InMenuCategory, FText InMenuName, FText InToolTip, UClass* InClass)
        : FEdGraphSchemaAction(InMenuCategory, InMenuName, InToolTip, 0), RuntimeNodeClass(InClass) {}

    virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override
    {
        UEdGraphNode_ExecGraph* NewVisualNode = NewObject<UEdGraphNode_ExecGraph>(ParentGraph);
        
        UExecNodeBase* NewRuntimeNode = NewObject<UExecNodeBase>(ParentGraph->GetOuter(), RuntimeNodeClass, NAME_None, RF_Transactional);
    	
        NewVisualNode->InitializeNode(NewRuntimeNode);
        NewVisualNode->NodePosX = Location.X;
        NewVisualNode->NodePosY = Location.Y;
    	
    	NewVisualNode->CreateNewGuid();
    	NewVisualNode->PostPlacedNewNode();
    	
        NewVisualNode->AllocateDefaultPins();
    	NewVisualNode->SetEnabledState(ENodeEnabledState::Enabled);
    	
    	ParentGraph->AddNode(NewVisualNode, bSelectNewNode, true);
    	
    	if (FromPin != nullptr)
    	{
    		NewVisualNode->GetSchema()->TryCreateConnection(FromPin, NewVisualNode->Pins[0]);
    	}
        return NewVisualNode;
    }
};

const FPinConnectionResponse UEdGraphSchema_ExecGraph::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot connect a node to itself."));
	}
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Must connect output to input."));
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT("Connect"));
}

FLinearColor UEdGraphSchema_ExecGraph::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White;
}


FConnectionDrawingPolicy* UEdGraphSchema_ExecGraph::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FExecGraphConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}
void UEdGraphSchema_ExecGraph::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	FText Category = NSLOCTEXT("ExecGraph", "NodesCategory", "Exec Graph Logic");

	const TArray<UClass*>& NodeClasses = FExecGraphEditorModule::GetCachedNodeClasses();

	for (UClass* NodeClass : NodeClasses)
	{
		FText MenuName = NodeClass->GetDisplayNameText();
		FText ToolTip = NodeClass->GetToolTipText(true);

		TSharedPtr<FExecGraphSchemaAction_NewNode> NewAction = MakeShareable(
			new FExecGraphSchemaAction_NewNode(Category, MenuName, ToolTip, NodeClass)
		);
        
		ContextMenuBuilder.AddAction(NewAction);
	}
}