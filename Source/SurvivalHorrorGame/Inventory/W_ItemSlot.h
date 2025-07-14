#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "W_ItemSlot.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Item Slot")
	FItemData CurrentItem;

	UPROPERTY(BlueprintReadWrite, Category = "Item Slot")
	int32 SlotIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* InventorySlotImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ItemAmountBorder;
	
	UFUNCTION(BlueprintCallable, Category = "Item Slot")
	void RefreshSlot();
	
protected:
	virtual void NativeConstruct() override;
};
