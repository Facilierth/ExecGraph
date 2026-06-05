// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ExecNode_Branch.h"

void UExecNode_Branch::OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	if (EvaluateStateCondition(Context, Tag, ComparisonType, ValueToCompare))
	{
		TriggerOutput(Context, Entry.Token, FName("True"));
	}
	else
	{
		TriggerOutput(Context, Entry.Token, FName("False"));
	}
}