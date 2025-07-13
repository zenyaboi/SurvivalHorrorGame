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

	FItemData()
	{
		ItemName = FText::GetEmpty();
		ItemDescription = FText::GetEmpty();
		isItemStackable = false;
		ItemAmount = 0;
		ItemMesh = nullptr;
		ItemImage = nullptr;
		isItemHealable = false;
		ItemHealAmount = 0;
	}
};