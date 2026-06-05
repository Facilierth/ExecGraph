// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ExecNode_Fork.h"

void UExecNode_Fork::OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry)
{
	// for EVERY connected output pin we push execution
	for (const auto& Kvp : Outputs)
	{
		TriggerOutput(Context, Entry.Token, Kvp.Key);
	}
}
