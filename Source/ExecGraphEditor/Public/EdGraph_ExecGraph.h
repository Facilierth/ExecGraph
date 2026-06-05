// Copyright (c) 2026, Jaroszyńska

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_ExecGraph.generated.h"

class UExecGraphAsset;

UCLASS()
class EXECGRAPHEDITOR_API UEdGraph_ExecGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UExecGraphAsset* ExecGraphAsset = nullptr;
};