#pragma once
#include "CoreMinimal.h"
#include "Misc/Guid.h"
#include "UObject/Object.h" 
#include "GameplayTagContainer.h"
#include "ExecTypes.generated.h"

// Simple token struct, it is basically a cursor in a db
// it tracks where are we now, we can move it forward, 
// cause it to execute something etc.
// if anything will come up in the future that the token
// needs to store, this is the place 
USTRUCT(BlueprintType)
struct EXECGRAPHRUNTIME_API FExecToken
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExecGraph")
	FGuid TokenId;

	FExecToken() : TokenId(FGuid::NewGuid()) {}
};

// the unit of work sitting in the fancy VM queue
USTRUCT(BlueprintType)
struct EXECGRAPHRUNTIME_API FExecExecutionEntry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExecGraph")
	FExecToken Token;

	// I kept as UObject to prevent the VM from depending on node asset classes
	// at runtime, the context will cast this to IExecNodeInterface.
	UPROPERTY()
	UObject* TargetNode = nullptr; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExecGraph")
	FName InputPin;

	FExecExecutionEntry() {}
	FExecExecutionEntry(const FExecToken& InToken, UObject* InNode, FName InPin)
		: Token(InToken), TargetNode(InNode), InputPin(InPin) {}
};

// kind of a memory for joins
USTRUCT(BlueprintType)
struct EXECGRAPHRUNTIME_API FJoinRuntimeState
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExecGraph")
	TSet<FName> ArrivedPins;
};