// Copyright (c) 2026, Jaroszyńska

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_ExecGraph.generated.h"

UCLASS()
class EXECGRAPHEDITOR_API UEdGraphSchema_ExecGraph : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	// when the user right-clicks the canvas
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	// what color should our execution pins be? (most important question)
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
};