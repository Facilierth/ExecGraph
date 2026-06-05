#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "ExecStateSubsystem.generated.h"

// Broadcasts: Tag, NewValue, OldValue
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnExecStateChanged, const FGameplayTag&, int32, int32);

/**
 * Global registry of integer-backed gameplay states.
 * 
 * Nodes may query state values directly, while waiting nodes
 * subscribe to state changes through the OnStateChanged delegate.
 *
 * Example:
 * Quest.Main.BanditsKilled = 3
 * Player.Reputation = 42
 */
UCLASS()
class EXECGRAPHRUNTIME_API UExecStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|State")
	void SetState(const FGameplayTag& Tag, int32 Value);

	/** Returns the current value for a state tag. Returns 0 if not found. */
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|State")
	int32 GetState(const FGameplayTag& Tag) const;

	/** Applies a delta to an existing state value. */
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|State")
	void ModifyState(const FGameplayTag& Tag, int32 Delta);

	FOnExecStateChanged& OnStateChanged() { return StateChangedDelegate; }

private:
	// Magical and wonderful central storage 
	// for all gameplay state values. 
	UPROPERTY()
	TMap<FGameplayTag, int32> StateRegistry;

	FOnExecStateChanged StateChangedDelegate;
};