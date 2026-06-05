#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExecTypes.h"
#include "ExecNodeInterface.generated.h"

class UExecContext;

UINTERFACE(MinimalAPI, Blueprintable)
class UExecNodeInterface : public UInterface { GENERATED_BODY() };

class EXECGRAPHRUNTIME_API IExecNodeInterface
{
	GENERATED_BODY()

public:
	virtual void ExecuteNode(UExecContext* Context, const FExecExecutionEntry& Entry) = 0;
};