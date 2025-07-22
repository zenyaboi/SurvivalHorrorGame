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

	SetupButtons();

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
	
	if (!Inventory || !Inventory->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory boo"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *CurrentItem.ItemName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Item Desc: %s"), *CurrentItem.ItemDescription.ToString());

	if (Inventory->ItemName)
    {
		Inventory->ItemName->SetText(CurrentItem.ItemName);
    }
	if (Inventory->ItemDescription)
	{
		Inventory->ItemDescription->SetText(CurrentItem.ItemDescription);
	}
}

void UW_ItemSlot::OnItemUnhovered()
{
	UE_LOG(LogTemp, Warning, TEXT("Item Unhovered"));
	
	if (!Inventory || !Inventory->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory boo"));
		return;
	}

	if (Inventory->ItemName)
	{
		Inventory->ItemName->SetText(FText::GetEmpty());
	}
	if (Inventory->ItemDescription)
	{
		Inventory->ItemDescription->SetText(FText::GetEmpty());
	}

	Selection->SetVisibility(ESlateVisibility::Hidden);
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
		if (InventoryGrid && IsValid(InventoryGrid) && InventoryGrid->HB_TopBar)
		{
			InventoryGrid->HB_TopBar->SetVisibility(ESlateVisibility::Visible);
			UE_LOG(LogTemp, Warning, TEXT("TopBar set to Visible"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("InventoryGrid or HB_TopBar is null"));
		}
		return;
	}

	Selection->SetCurrentItem(CurrentItem);
	Selection->SetVisibility(ESlateVisibility::Visible);
	if (InventoryGrid && IsValid(InventoryGrid) && InventoryGrid->HB_TopBar)
	{
		InventoryGrid->HB_TopBar->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("TopBar set to Hidden"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryGrid or HB_TopBar is null"));
	}
}

void UW_ItemSlot::SetupButtons()
{
	UButton* BtnHeal = Cast<UButton>(Selection->GetWidgetFromName("BTN_Heal"));
	UButton* BtnCombine = Cast<UButton>(Selection->GetWidgetFromName("BTN_Combine"));
	UButton* BtnInspect = Cast<UButton>(Selection->GetWidgetFromName("BTN_Inspect"));
	UButton* BtnDelete = Cast<UButton>(Selection->GetWidgetFromName("BTN_Delete"));

	Selection->BindHealButtonEvent(BtnHeal);
	Selection->BindCombineButtonEvent(BtnCombine);
	Selection->BindInspectButtonEvent(BtnInspect);
	Selection->BindDeleteButtonEvent(BtnDelete);
	Selection->OnHealEvent.AddDynamic(this, &UW_ItemSlot::OnHealEventTriggered);
	Selection->OnCombineEvent.AddDynamic(this, &UW_ItemSlot::OnCombineEventTriggered);
	Selection->OnInspectEvent.AddDynamic(this, &UW_ItemSlot::OnInspectEventTriggered);
	Selection->OnDeleteEvent.AddDynamic(this, &UW_ItemSlot::OnDeleteEventTriggered);
}

void UW_ItemSlot::OnHealEventTriggered(FItemData ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("BITCHES ARE TRIPPING"));
}

void UW_ItemSlot::OnCombineEventTriggered(FItemData ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("BITCHES ARE TRIPPING"));
}

void UW_ItemSlot::OnInspectEventTriggered(FItemData ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("BITCHES ARE TRIPPING"));
	
	SpawnActor(PlayerController, InventoryGrid);
}

void UW_ItemSlot::OnDeleteEventTriggered(APlayerController* PlayerControllerRef, FItemData CurrentItemRef)
{
	UE_LOG(LogTemp, Warning, TEXT("BITCHES ARE TRIPPING"));
}

void UW_ItemSlot::SpawnActor(APlayerController* Player, UW_InventoryGrid* InventoryRef)
{
	UE_LOG(LogTemp, Warning, TEXT("HEY"));

	if (!InspectItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("InspectItemClass não está definido!"));
		return;
	}
	
	FVector SpawnLocation = FVector(10000000.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = CurrentActorItem;
	SpawnParams.Instigator = CurrentActorItem->GetInstigator();

	AInspectItem* newItem = GetWorld()->SpawnActor<AInspectItem>(
		InspectItemClass,
		SpawnLocation,
		SpawnRotation
		);

	if (!Inventory)
		return;
	
	IInteract::Execute_Inspect(newItem, Player, CurrentItem.ItemMesh, CurrentItem.ItemName, CurrentItem.ItemDescription, InventoryRef);
}