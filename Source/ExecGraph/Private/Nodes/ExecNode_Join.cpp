// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ExecNode_Join.h"

void UExecNode_Join::OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	FJoinRuntimeState& State = Context->GetOrCreateJoinState(this);
	
	State.ArrivedPins.Add(Entry.InputPin);
	
	if (State.ArrivedPins.Num() >= ExpectedInputs)
	{
		Context->ClearJoinState(this);
		
		TriggerOutput(Context, Entry.Token, FName("Completed"));
	}
}
