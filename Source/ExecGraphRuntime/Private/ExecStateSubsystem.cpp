#include "ExecStateSubsystem.h"

void UExecStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UExecStateSubsystem::Deinitialize()
{
	StateRegistry.Empty();
	Super::Deinitialize();
}

void UExecStateSubsystem::SetState(const FGameplayTag& Tag, int32 Value)
{
	if (!Tag.IsValid()) return;

	int32 OldValue = StateRegistry.FindRef(Tag);
	if (OldValue != Value)
	{
		StateRegistry.FindOrAdd(Tag) = Value;
		StateChangedDelegate.Broadcast(Tag, Value, OldValue);
	}
}

int32 UExecStateSubsystem::GetState(const FGameplayTag& Tag) const
{
	if (!Tag.IsValid()) return 0;
    
	if (const int32* ValuePtr = StateRegistry.Find(Tag))
	{
		return *ValuePtr;
	}
	return 0;
}

void UExecStateSubsystem::ModifyState(const FGameplayTag& Tag, int32 Delta)
{
	if (!Tag.IsValid() || Delta == 0) return;
	SetState(Tag, GetState(Tag) + Delta);
}