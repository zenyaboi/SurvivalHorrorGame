#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "S_ItemData.h"
#include "W_InventoryGrid.h"
#include "Components/TextBlock.h"
#include "SurvivalHorrorGame/Items/BaseItem.h"
#include "W_Inventory.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FItemData> Items;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<ABaseItem*> ActorItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemDescription;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* WrapBoxInventory;
};
