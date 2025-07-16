#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "W_InventoryGrid.h"
#include "Components/TextBlock.h"
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
	class UButton* ItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* InventorySlotImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ItemAmountBorder;
	
	UFUNCTION(BlueprintCallable, Category = "Item Slot")
	void RefreshSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> WInventoryGridClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UW_InventoryGrid* InventoryGrid;

	UFUNCTION()
	void OnItemHovered();
	UFUNCTION()
	void OnItemUnhovered();
protected:
	virtual void NativeConstruct() override;
};
