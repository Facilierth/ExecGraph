// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "ExecNodeBase.h"
#include "GameplayTagContainer.h"
#include "ExecNode_WaitForTag.generated.h"

UCLASS(DisplayName = "Wait For State")
class EXECGRAPH_API UExecNode_WaitForTag : public UExecNodeBase
{
	GENERATED_BODY()

public:
	UExecNode_WaitForTag()
	{
		TargetValue = 1;
		ComparisonType = EComparisonType::GreaterThanOrEqualTo;
	}
    
	UPROPERTY(EditAnywhere, Category = "Logic")
	EComparisonType ComparisonType;
	
	UPROPERTY(EditAnywhere, Category = "Logic")
	FGameplayTag TargetTag;
	
	UPROPERTY(EditAnywhere, Category = "Logic")
	int32 TargetValue; 

protected:
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry) override;
};