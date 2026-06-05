#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ExecGraphFactory.generated.h"

UCLASS()
class EXECGRAPHEDITOR_API UExecGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	UExecGraphFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};