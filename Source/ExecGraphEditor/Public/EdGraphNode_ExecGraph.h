// Copyright (c) 2026, Jaroszyńska

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Nodes/ExecNodeBase.h"
#include "EdGraphNode_ExecGraph.generated.h"

UCLASS()
class EXECGRAPHEDITOR_API UEdGraphNode_ExecGraph : public UEdGraphNode
{
	GENERATED_BODY()

public:
	// actual node that this visual box represents
	UPROPERTY(VisibleAnywhere, Category = "Runtime Instance")
	UExecNodeBase* RuntimeNode = nullptr;

	// default input/output pins based on the node type
	virtual void AllocateDefaultPins() override;
    
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    
	virtual FLinearColor GetNodeTitleColor() const override;

	void InitializeNode(UExecNodeBase* InRuntimeNode);
};