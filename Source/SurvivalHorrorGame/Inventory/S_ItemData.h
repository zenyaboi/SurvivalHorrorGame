#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Components/StaticMeshComponent.h"
#include "S_ItemData.generated.h"

USTRUCT(BlueprintType)
struct SURVIVALHORRORGAME_API FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isItemInventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isItemStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isItemHealable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemHealAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator ItemInspectionRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ItemInspectionScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isItemCraftable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ItemsToCraft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*>ItemsToCraftImage;

	bool operator==(const FItemData& Other) const
	{
		return isItemInventory == Other.isItemInventory &&
			ItemName.ToString() == Other.ItemName.ToString() && ItemDescription.ToString() == Other.ItemDescription.ToString() &&
				isItemStackable == Other.isItemStackable && ItemAmount == Other.ItemAmount &&
					ItemMesh == Other.ItemMesh && ItemImage == Other.ItemImage &&
						isItemHealable == Other.isItemHealable && ItemHealAmount == Other.ItemHealAmount &&
							ItemInspectionRotation == Other.ItemInspectionRotation && ItemInspectionScale == Other.ItemInspectionScale &&
								isItemCraftable == Other.isItemCraftable;
	}

	bool operator!=(const FItemData& Other) const
	{
		return !(*this == Other);
	}

	FItemData()
	{
		isItemInventory = true;
		ItemName = FText::GetEmpty();
		ItemDescription = FText::GetEmpty();
		isItemStackable = false;
		ItemAmount = 0;
		ItemMesh = nullptr;
		ItemImage = nullptr;
		isItemHealable = false;
		ItemHealAmount = 0;
		ItemInspectionRotation = FRotator::ZeroRotator;
		ItemInspectionScale = FVector::OneVector;
	}
};