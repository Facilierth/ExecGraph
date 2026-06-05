// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExecNodeBase.h"
#include "ExecNode_Fork.generated.h"

UCLASS(DisplayName = "Fork (Parallel Split)")
class EXECGRAPH_API UExecNode_Fork : public UExecNodeBase
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual FLinearColor GetNodeColor() const override
	{
		return FLinearColor::Blue;
	}
#endif
protected:
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry) override;
};