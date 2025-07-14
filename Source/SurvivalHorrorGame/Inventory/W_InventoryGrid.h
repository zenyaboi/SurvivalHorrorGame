#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "W_InventoryGrid.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FItemData> Items;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* WrapBoxInventory;
};
