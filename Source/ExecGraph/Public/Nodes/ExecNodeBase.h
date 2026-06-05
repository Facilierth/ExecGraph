#pragma once

#include "CoreMinimal.h"
#include "ExecNodeInterface.h"
#include "ExecContext.h"
#include "GameplayTagContainer.h"
#include "ExecNodeBase.generated.h"

UENUM(BlueprintType)
enum class EComparisonType : uint8
{
	GreaterThan,
	GreaterThanOrEqualTo,
	LessThan,
	LessThanOrEqualTo,
	EqualTo,
	NotEqualTo
};

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class EXECGRAPH_API UExecNodeBase : public UObject, public IExecNodeInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Wiring")
	TMap<FName, UExecNodeBase*> Outputs;

	virtual void ExecuteNode(UExecContext* Context, const FExecExecutionEntry& Entry) override final;
	
    virtual TArray<FName> GetOutputPinNames() const
    {
        return { FName("Out") };
    }
	
#if WITH_EDITOR
	virtual FLinearColor GetNodeColor() const
	{
    	return FLinearColor::Gray;
	}
#endif
	
protected:
	virtual void OnExecuted(UExecContext* Context, const FExecExecutionEntry& Entry);

	void TriggerOutput(UExecContext* Context, const FExecToken& Token, FName OutputPin);

	static bool EvaluateStateCondition(UExecContext* Context, const FGameplayTag& Tag, EComparisonType CompType, int32 TargetValue);
};