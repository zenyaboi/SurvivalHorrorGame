#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_ItemData.h"
#include "W_InventoryGrid.h"
#include "SurvivalHorrorGame/Player/PlayerCharacter.h"
#include "W_ItemSlot.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	FItemData CurrentItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Slot")
	int32 SlotIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* InventorySlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Selection", meta = (BindWidget))
	class UW_Selection* Selection;

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
	UFUNCTION()
	void OnClicked();

	// Trigger Events
	UFUNCTION()
	void OnHealEventTriggered(FItemData ItemData);
	UFUNCTION()
	void OnCombineEventTriggered(FItemData ItemData);
	UFUNCTION()
	void OnInspectEventTriggered(FItemData ItemData);
	UFUNCTION()
	void OnDeleteEventTriggered(FItemData ItemData);
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	APlayerController* PlayerController;

	void SetupButtons();
};
