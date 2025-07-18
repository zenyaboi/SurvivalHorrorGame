#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "S_ItemData.h"
#include "Components/TextBlock.h"
#include "W_InventoryGrid.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API UW_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FItemData> Items;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize;

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
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
