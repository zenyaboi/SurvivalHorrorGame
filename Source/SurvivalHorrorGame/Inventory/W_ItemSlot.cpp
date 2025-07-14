#include "SurvivalHorrorGame/Inventory/W_ItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Engine/Texture2D.h"

void UW_ItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshSlot();
}

void UW_ItemSlot::RefreshSlot()
{
	if (CurrentItem.ItemImage && IsValid(CurrentItem.ItemImage))
	{
		if (InventorySlotImage)
		{
			InventorySlotImage->SetBrushFromTexture(CurrentItem.ItemImage);
		}

		if (CurrentItem.isItemStackable && CurrentItem.ItemAmount > 1)
		{
			if (ItemAmount)
			{
				ItemAmount->SetText(FText::AsNumber(CurrentItem.ItemAmount));
			}
			if (ItemAmountBorder)
			{
				ItemAmountBorder->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (ItemAmountBorder)
			{
				ItemAmountBorder->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		if (ItemAmountBorder)
		{
			ItemAmountBorder->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}