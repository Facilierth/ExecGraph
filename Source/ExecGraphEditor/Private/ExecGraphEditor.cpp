#include "ExecGraphEditor.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetActions_ExecGraph.h"

#define LOCTEXT_NAMESPACE "FExecGraphEditorModule"

void FExecGraphEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	TSharedRef<IAssetTypeActions> Action = MakeShareable(new FAssetTypeActions_ExecGraph());
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetActions.Add(Action);
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
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FExecGraphEditorModule, ExecGraphEditor)