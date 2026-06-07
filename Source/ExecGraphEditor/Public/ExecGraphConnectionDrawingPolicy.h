// Copyright (c) 2026, Jaroszyńska

#pragma once

#include "CoreMinimal.h"
#include "ConnectionDrawingPolicy.h"

class EXECGRAPHEDITOR_API FExecGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	UEdGraph* GraphObj;

	FExecGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);

	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params) override;

private:
	float WireThickness = 1.5f;
	bool bDrawBubbles = false;
};