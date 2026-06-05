#pragma once

#include "CoreMinimal.h"
#include "Nodes/ExecNodeBase.h"
#include "GameplayTagContainer.h"
#include "ExecNode_Branch.generated.h"

UCLASS(DisplayName="Branch (State)")
class EXECGRAPH_API UExecNode_Branch : public UExecNodeBase
{
	GENERATED_BODY()

public:
	UExecNode_Branch() 
	{
		ValueToCompare = 1;
		ComparisonType = EComparisonType::GreaterThanOrEqualTo;
	}

	UPROPERTY(EditAnywhere, Category = "Logic")
	FGameplayTag Tag;
    
	UPROPERTY(EditAnywhere, Category = "Logic")
	int32 ValueToCompare;
    
	UPROPERTY(EditAnywhere, Category = "Logic")
	EComparisonType ComparisonType;
	
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry) override;
};