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

protected:
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry) override;
};