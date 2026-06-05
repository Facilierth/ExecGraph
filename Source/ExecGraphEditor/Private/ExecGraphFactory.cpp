#include "ExecGraphFactory.h"
#include "ExecGraphAsset.h"

UExecGraphFactory::UExecGraphFactory()
{
	SupportedClass = UExecGraphAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UExecGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
                                             UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UExecGraphAsset>(InParent, Class, Name, Flags);
}