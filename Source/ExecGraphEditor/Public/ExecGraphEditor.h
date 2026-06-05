#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTypeActions.h"

class FExecGraphEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static const TArray<UClass*>& GetCachedNodeClasses();

private:
    static void RebuildNodeCache();

    TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetActions;
    
    static TArray<UClass*> CachedNodeClasses;
};