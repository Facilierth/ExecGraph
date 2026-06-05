#include "Nodes/ExecNodeBase.h"
#include "ExecContext.h"
#include "ExecStateSubsystem.h"

void UExecNodeBase::ExecuteNode(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	OnExecuted(Context, Entry);
}

void UExecNodeBase::OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	// Base does nothing, zzz
}

void UExecNodeBase::TriggerOutput(UExecContext* Context, const FExecToken& Token, FName OutputPin)
{
	if (!Context) return;

	if (UExecNodeBase** TargetNodePtr = Outputs.Find(OutputPin))
	{
		if (UExecNodeBase* TargetNode = *TargetNodePtr)
		{
			Context->PushExecution(Token, TargetNode, OutputPin);
		}
	}
}

bool UExecNodeBase::EvaluateStateCondition(UExecContext* Context, const FGameplayTag& Tag, EComparisonType CompType, int32 TargetValue)
{
	UExecStateSubsystem* State = Context ? Context->GetStateSubsystem() : nullptr;
	if (!State) return false;

	const int32 CurrentValue = State->GetState(Tag);

	switch (CompType)
	{
	case EComparisonType::EqualTo:              return CurrentValue == TargetValue;
	case EComparisonType::NotEqualTo:           return CurrentValue != TargetValue;
	case EComparisonType::GreaterThan:          return CurrentValue > TargetValue;
	case EComparisonType::LessThan:             return CurrentValue < TargetValue;
	case EComparisonType::GreaterThanOrEqualTo: return CurrentValue >= TargetValue;
	case EComparisonType::LessThanOrEqualTo:    return CurrentValue <= TargetValue;
	}
	return false;
}