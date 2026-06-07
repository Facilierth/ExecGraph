// Copyright (c) 2026, Jaroszyńska


#include "ExecGraphConnectionDrawingPolicy.h"

FExecGraphConnectionDrawingPolicy::FExecGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID,
	float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj): FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements)
	, GraphObj(InGraphObj)
{
}

void FExecGraphConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
                                                             FConnectionParams& Params)
{
	Params.WireThickness = WireThickness; 
	Params.bDrawBubbles = bDrawBubbles; 
		
	if (OutputPin && GraphObj && GraphObj->GetSchema())
		Params.WireColor = GraphObj->GetSchema()->GetPinTypeColor(OutputPin->PinType);
	else
		Params.WireColor = FLinearColor::White;
}
