// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ExecNode_WaitForTag.h"

void UExecNode_WaitForTag::OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	if (EvaluateStateCondition(Context, TargetTag, ComparisonType, TargetValue))
	{
		TriggerOutput(Context, Entry.Token, FName("Completed"));
	}
	else
	{
		Context->SleepEntry(Entry, TargetTag);
	}
}