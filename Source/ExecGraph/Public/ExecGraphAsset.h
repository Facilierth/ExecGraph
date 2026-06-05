#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExecGraphAsset.generated.h"

class UExecNodeBase;
class UExecContext;

#if WITH_EDITORONLY_DATA
class UEdGraph;
#endif

UCLASS(BlueprintType, Category = "ExecGraph")
class EXECGRAPH_API UExecGraphAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Graph Data")
	UExecNodeBase* EntryNode;

	UPROPERTY(VisibleAnywhere, Category = "Graph Data")
	TArray<UExecNodeBase*> AllNodes;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UEdGraph* EdGraph = nullptr;
#endif

	// Spawns a runtime execution context and starts the graph "pulse"
	UFUNCTION(BlueprintCallable, Category = "ExecGraph|Runtime")
	UExecContext* StartGraphInstance(UObject* OwnerContext, UExecStateSubsystem* StateSubsystem);
};