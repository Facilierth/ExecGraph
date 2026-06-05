// Copyright (c) 2026, Jaroszyńska

#include "EdGraphNode_ExecGraph.h"
#include "EdGraph/EdGraphPin.h"

void UEdGraphNode_ExecGraph::InitializeNode(UExecNodeBase* InRuntimeNode)
{
    RuntimeNode = InRuntimeNode;
}
void UEdGraphNode_ExecGraph::AllocateDefaultPins()
{
    if (!RuntimeNode) return;
    
    CreatePin(EGPD_Input, TEXT("Exec"), FName(), TEXT("In"));
    
    TArray<FName> OutputPinNames = RuntimeNode->GetOutputPinNames();
    
    for (const FName& PinName : OutputPinNames)
    {
        CreatePin(EGPD_Output, TEXT("Exec"), FName(), PinName);
    }
}

FText UEdGraphNode_ExecGraph::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    if (RuntimeNode)
    {
        return RuntimeNode->GetClass()->GetDisplayNameText();
    }
    return NSLOCTEXT("ExecGraph", "UnknownNode", "Unknown Node");
}

FLinearColor UEdGraphNode_ExecGraph::GetNodeTitleColor() const
{
    return RuntimeNode ? RuntimeNode->GetNodeColor() : FLinearColor::White;
}