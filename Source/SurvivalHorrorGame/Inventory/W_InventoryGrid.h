#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "S_ItemData.h"
#include "SurvivalHorrorGame/Items/BaseItem.h"
#include "W_InventoryGrid.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* InventorySwitcher;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UW_Inventory* W_InventoryWidget;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UW_Combine* W_CombineWidget;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FItemData> Items;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize = 20;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<ABaseItem*> ActorItems;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchToInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchToCombine();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UW_Inventory* GetInventoryWidget() const { return W_InventoryWidget; }
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	int32 CurrentTabIndex = 0;
};
