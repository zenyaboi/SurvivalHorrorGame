#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InspectItem.h"
#include "W_Inspect.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_Inspect : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UW_InventoryGrid* InventoryGrid;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inspect")
	AInspectItem* InspectItemRef;
protected:
	virtual void NativeConstruct() override;
	
	bool IsLeftMousePressed = false;
	bool IsRightMousePressed = false;
	FVector2D LastMousePosition;

	// Mouse Input Functions
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
