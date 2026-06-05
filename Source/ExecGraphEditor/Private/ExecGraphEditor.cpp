#include "ExecGraphEditor.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetActions_ExecGraph.h"
#include "Nodes/ExecNodeBase.h"

#define LOCTEXT_NAMESPACE "FExecGraphEditorModule"

TArray<UClass*> FExecGraphEditorModule::CachedNodeClasses;

void FExecGraphEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	TSharedRef<IAssetTypeActions> Action = MakeShareable(new FAssetTypeActions_ExecGraph());
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetActions.Add(Action);
	
	RebuildNodeCache();
}

void FExecGraphEditorModule::RebuildNodeCache()
{
	CachedNodeClasses.Empty();

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		if (Class->IsChildOf(UExecNodeBase::StaticClass()) && 
			!Class->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists))
		{
			CachedNodeClasses.Add(Class);
		}
	}
}

const TArray<UClass*>& FExecGraphEditorModule::GetCachedNodeClasses()
{
	if (CachedNodeClasses.Num() == 0)
	{
		RebuildNodeCache();
	}
	return CachedNodeClasses;
}

void FExecGraphEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (auto Action : RegisteredAssetActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
	RegisteredAssetActions.Empty();
	
	CachedNodeClasses.Empty();
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FExecGraphEditorModule, ExecGraphEditor)