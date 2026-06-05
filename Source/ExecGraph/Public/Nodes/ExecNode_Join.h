// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExecNodeBase.h"
#include "ExecNode_Join.generated.h"


UCLASS(DisplayName = "Join (Synchronize)")
class EXECGRAPH_API UExecNode_Join : public UExecNodeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Logic")
	int32 ExpectedInputs = 2;

	virtual TArray<FName> GetOutputPinNames() const override
	{
		return { FName("Completed") };
	}
	
#if WITH_EDITOR
	virtual FLinearColor GetNodeColor() const
	{
		return FLinearColor::Blue;
	}
#endif
protected:
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry) override;
};