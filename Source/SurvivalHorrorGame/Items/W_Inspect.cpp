#include "W_Inspect.h"
#include "InspectItem.h" 

void UW_Inspect::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetIsFocusable(true);
	SetKeyboardFocus();

	LastMousePosition = FVector2D::ZeroVector;
	IsLeftMousePressed = false;
	IsRightMousePressed = false;
}

FReply UW_Inspect::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InspectItemRef && IsValid(InspectItemRef) && IsLeftMousePressed)
	{
		FVector2D CurrentMousePosition = InMouseEvent.GetScreenSpacePosition();
		
		if (!LastMousePosition.IsZero())
		{
			FVector2D MouseDelta = CurrentMousePosition - LastMousePosition;

			MouseDelta *= 0.5f;
			
			InspectItemRef->ReceiveMouseInput(MouseDelta.X, -MouseDelta.Y);
		}
		
		LastMousePosition = CurrentMousePosition;
	}
	else if (!IsLeftMousePressed)
	{
		// Update mouse position even when not rotating for smooth transitions
		LastMousePosition = InMouseEvent.GetScreenSpacePosition();
	}
	
	return FReply::Handled();
}

FReply UW_Inspect::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InspectItemRef && IsValid(InspectItemRef))
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			IsLeftMousePressed = true;
			InspectItemRef->HandleLeftMousePressed();
			
			LastMousePosition = InMouseEvent.GetScreenSpacePosition();

			return FReply::Handled().CaptureMouse(TakeWidget());
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			IsRightMousePressed = true;
			InspectItemRef->HandleRightMousePressed();
		}
	}
	
	return FReply::Handled();
}

FReply UW_Inspect::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InspectItemRef && IsValid(InspectItemRef))
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			IsLeftMousePressed = false;
			InspectItemRef->HandleLeftMouseReleased();

			return FReply::Handled().ReleaseMouseCapture();
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			IsRightMousePressed = false;
			InspectItemRef->HandleRightMouseReleased();
		}
	}
	
	return FReply::Handled();
}

FReply UW_Inspect::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InspectItemRef && IsValid(InspectItemRef))
	{
		float WheelDelta = InMouseEvent.GetWheelDelta();
		
		if (WheelDelta > 0)
		{
			InspectItemRef->HandleMouseWheelScrollUp();
		}
		else if (WheelDelta < 0)
		{
			InspectItemRef->HandleMouseWheelScrollDown();
		}
	}
	
	return FReply::Handled();
}

FReply UW_Inspect::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (InspectItemRef && IsValid(InspectItemRef))
		{
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				InspectItemRef->CloseInspect(PC);
			}
		}
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
