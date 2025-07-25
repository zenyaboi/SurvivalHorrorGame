#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_ItemData.h"
#include "SurvivalHorrorGame/Items/BaseItem.h"
#include "Blueprint/UserWidget.h"
#include "W_InventoryGrid.h"
#include "InventoryComponent.generated.h"

// Struct Check Stack
USTRUCT(BlueprintType)
struct FStackCheckResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool CanStack;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 NewQuantity;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool ReachedMaxStack;

	FStackCheckResult()
	{
		CanStack = false;
		NewQuantity = 0;
		ReachedMaxStack = false;
	}
};

// Struct Add Item
USTRUCT(BlueprintType)
struct FAddItemResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool WasAdded;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 TargetSlotIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool WasStacked;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 FinalQuantity;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	FString ErrorMessage;

	FAddItemResult()
	{
		WasAdded = false;
		TargetSlotIndex = -1;
		WasStacked = false;
		FinalQuantity = 0;
		ErrorMessage = TEXT("");
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALHORRORGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	class UUserWidget* InventoryReference;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	UW_InventoryGrid* InventoryGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemData> Items;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<ABaseItem*> ActorItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventorySize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32, FText> InventoryMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> WInventoryGridClass;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FAddItemResult AddItemToInventory(ABaseItem* Actor, FItemData NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FStackCheckResult ShouldStackItems(FItemData itemFromInv, FItemData itemCurrentActor);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 FindEmptySlot();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool hasSpaceInventory(int32 amountInInv);

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool isInventoryVisible;

	void DestroyItem(ABaseItem* Item);
protected:
	int32 currentStack;
	int32 maxStack;

	FItemData LocalItem;
};
