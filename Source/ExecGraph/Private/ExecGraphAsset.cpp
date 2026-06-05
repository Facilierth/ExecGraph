// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecGraphAsset.h"
#include "Nodes/ExecNodeBase.h"
#include "ExecContext.h"
#include "Engine/World.h"

UExecContext* UExecGraphAsset::StartGraphInstance(UObject* OwnerContext, UExecStateSubsystem* StateSubsystem)
{
	if (!EntryNode || !OwnerContext || !StateSubsystem) return nullptr;
	
	UExecContext* Context = NewObject<UExecContext>(OwnerContext);
	Context->InitializeContext(OwnerContext, StateSubsystem);
	
	FExecToken StartToken;
	
	Context->PushExecution(StartToken, EntryNode, FName("Start"));
	Context->ProcessExecutionQueue();

	return Context;
}