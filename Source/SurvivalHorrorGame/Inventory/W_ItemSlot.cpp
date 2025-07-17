#include "W_ItemSlot.h"
#include "W_Selection.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"

void UW_ItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = GetWorld()->GetFirstPlayerController();

	UButton* BtnHeal = Cast<UButton>(Selection->GetWidgetFromName("BTN_Heal"));

	Selection->BindHealButtonEvent(BtnHeal);
	Selection->OnHealEvent.AddDynamic(this, &UW_ItemSlot::OnHealEventTriggered);

	if (ItemButton)
	{
		ItemButton->OnHovered.AddDynamic(this, &UW_ItemSlot::OnItemHovered);
		ItemButton->OnUnhovered.AddDynamic(this, &UW_ItemSlot::OnItemUnhovered);
		ItemButton->OnClicked.AddDynamic(this, &UW_ItemSlot::OnClicked);
	}
	
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

		if (CurrentItem.isItemStackable && CurrentItem.ItemAmount >= 1)
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

void UW_ItemSlot::OnItemHovered()
{
	UE_LOG(LogTemp, Warning, TEXT("Item hovered"));
	
	if (!InventoryGrid || !InventoryGrid->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory boo"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *CurrentItem.ItemName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Item Desc: %s"), *CurrentItem.ItemDescription.ToString());

	if (InventoryGrid->ItemName)
    {
		InventoryGrid->ItemName->SetText(CurrentItem.ItemName);
    }
	if (InventoryGrid->ItemDescription)
	{
		InventoryGrid->ItemDescription->SetText(CurrentItem.ItemDescription);
	}
}

void UW_ItemSlot::OnItemUnhovered()
{
	UE_LOG(LogTemp, Warning, TEXT("Item Unhovered"));
	
	if (!InventoryGrid || !InventoryGrid->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory boo"));
		return;
	}

	if (InventoryGrid->ItemName)
	{
		InventoryGrid->ItemName->SetText(FText::GetEmpty());
	}
	if (InventoryGrid->ItemDescription)
	{
		InventoryGrid->ItemDescription->SetText(FText::GetEmpty());
	}
}

void UW_ItemSlot::OnClicked()
{
	if (!IsValid(CurrentItem.ItemImage))
		return;

	UE_LOG(LogTemp, Warning, TEXT("Item Clicked"));

	if (!Selection)
		return;

	if (Selection->GetVisibility() == ESlateVisibility::Visible)
	{
		Selection->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	
	Selection->SetVisibility(ESlateVisibility::Visible);
}

void UW_ItemSlot::OnHealEventTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("BITCHES ARE TRIPPING"));
}
