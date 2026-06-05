#include "ExecContext.h"
#include "ExecStateSubsystem.h"
#include "ExecNodeInterface.h"

void UExecContext::InitializeContext(UObject* InOwner, UExecStateSubsystem* InStateSubsystem)
{
    ContextOwner = InOwner;
    StateSubsystem = InStateSubsystem;

    if (StateSubsystem.IsValid())
    {
        StateSubsystem->OnStateChanged().AddUObject(this, &UExecContext::HandleStateChanged);
    }
}

void UExecContext::DeinitializeContext()
{
    if (StateSubsystem.IsValid())
    {
        StateSubsystem->OnStateChanged().RemoveAll(this);
    }
    ExecutionQueue.Empty();
    SleepingEntries.Empty();
    JoinStates.Empty();
}

void UExecContext::PushExecution(const FExecToken& Token, UObject* TargetNode, FName InputPin)
{
    if (TargetNode)
    {
        ExecutionQueue.Add(FExecExecutionEntry(Token, TargetNode, InputPin));
    }
}

void UExecContext::ProcessExecutionQueue(int32 MaxInstructions)
{
    int32 InstructionsProcessed = 0;

    while (ExecutionQueue.Num() > 0 && InstructionsProcessed < MaxInstructions)
    {
        // FIFO
        FExecExecutionEntry CurrentEntry = ExecutionQueue[0];
        ExecutionQueue.RemoveAt(0);

        if (CurrentEntry.TargetNode)
        {
            if (IExecNodeInterface* NodeInterface = Cast<IExecNodeInterface>(CurrentEntry.TargetNode))
            {
                InstructionsProcessed++;
                NodeInterface->ExecuteNode(this, CurrentEntry);
            }
        }
    }
    
    if (ExecutionQueue.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecGraph: Frame budget exceeded. Deferring remaining instructions."));
    }
}

void UExecContext::SleepEntry(const FExecExecutionEntry& Entry, const FGameplayTag& Tag)
{
    SleepingEntries.FindOrAdd(Tag).Add(Entry);
}

void UExecContext::HandleStateChanged(const FGameplayTag& Tag, int32 NewValue, int32 OldValue)
{
    // Did anyone care about this tag changing?
    if (TArray<FExecExecutionEntry>* WokenEntries = SleepingEntries.Find(Tag))
    {
        // Yes! Put all their exact saved entries back into the active VM queue
        for (const FExecExecutionEntry& Entry : *WokenEntries)
        {
            ExecutionQueue.Add(Entry);
        }
        
        SleepingEntries.Remove(Tag);
        
        ProcessExecutionQueue();
    }
}
FJoinRuntimeState& UExecContext::GetOrCreateJoinState(UObject* JoinNode)
{
    return JoinStates.FindOrAdd(JoinNode);
}

void UExecContext::ClearJoinState(UObject* JoinNode)
{
    JoinStates.Remove(JoinNode);
}

UExecStateSubsystem* UExecContext::GetStateSubsystem() const
{
    return StateSubsystem.Get();
}
