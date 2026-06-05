#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExecTypes.h"
#include "GameplayTagContainer.h"
#include "ExecContext.generated.h"

class UExecStateSubsystem;

UCLASS(BlueprintType)
class EXECGRAPHRUNTIME_API UExecContext : public UObject
{
	GENERATED_BODY()

public:
	void InitializeContext(UObject* InOwner, UExecStateSubsystem* InStateSubsystem);
	void DeinitializeContext();

	// the global identity of this specific graph run
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|Context")
	UObject* GetContextOwner() const { return ContextOwner; }

	// queue management
	void PushExecution(const FExecToken& Token, UObject* TargetNode, FName InputPin);
    
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|VM")
	void ProcessExecutionQueue(int32 MaxInstructions = 100);

	void SleepEntry(const FExecExecutionEntry& Entry, const FGameplayTag& Tag);
	
	FJoinRuntimeState& GetOrCreateJoinState(UObject* JoinNode);
	void ClearJoinState(UObject* JoinNode);
	
	UExecStateSubsystem* GetStateSubsystem() const;

private:
	void HandleStateChanged(const FGameplayTag& Tag, int32 NewValue, int32 OldValue);

	UPROPERTY()
	UObject* ContextOwner = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UExecStateSubsystem> StateSubsystem;

	// the FIFO Queue
	UPROPERTY()
	TArray<FExecExecutionEntry> ExecutionQueue;

	TMap<FGameplayTag, TArray<FExecExecutionEntry>> SleepingEntries;
	
	TMap<UObject*, FJoinRuntimeState> JoinStates;
};