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
};
