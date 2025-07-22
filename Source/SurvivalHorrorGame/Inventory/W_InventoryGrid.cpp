#include "W_InventoryGrid.h"
#include "W_Inventory.h"
#include "W_Combine.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryComponent.h"

void UW_InventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();
    
	SetIsFocusable(true);
	
	if (InventorySwitcher)
	{
		InventorySwitcher->SetActiveWidgetIndex(0);
		CurrentTabIndex = 0;
	}
	
	if (W_InventoryWidget)
	{
		W_InventoryWidget->Items = Items;
		W_InventoryWidget->InventorySize = InventorySize;
		W_InventoryWidget->ActorItems = ActorItems;
	}
}

void UW_InventoryGrid::RefreshInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("InventoryGrid: RefreshInventory chamado"));
	
	if (W_InventoryWidget)
	{
		W_InventoryWidget->Items = Items;
		W_InventoryWidget->InventorySize = InventorySize;
		W_InventoryWidget->ActorItems = ActorItems;
		
		W_InventoryWidget->RefreshInventory();
	}
}

void UW_InventoryGrid::SwitchToInventory()
{
	if (InventorySwitcher)
	{
		InventorySwitcher->SetActiveWidgetIndex(0);
		CurrentTabIndex = 0;
		UE_LOG(LogTemp, Warning, TEXT("Switched to Inventory tab"));
		
		RefreshInventory();
	}
}

void UW_InventoryGrid::SwitchToCombine()
{
	if (InventorySwitcher)
	{
		InventorySwitcher->SetActiveWidgetIndex(1);
		CurrentTabIndex = 1;
		UE_LOG(LogTemp, Warning, TEXT("Switched to Combine tab"));
	}
}

FReply UW_InventoryGrid::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		SwitchToInventory();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::E)
	{
		SwitchToCombine();
		return FReply::Handled();
	}
	
	if (InKeyEvent.GetKey() == EKeys::Tab || InKeyEvent.GetKey() == EKeys::I || InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (AActor* Owner = GetOwningPlayerPawn())
		{
			if (UInventoryComponent* InventoryComp = Owner->FindComponentByClass<UInventoryComponent>())
			{
				InventoryComp->ToggleInventory();
				return FReply::Handled();
			}
		}
	}
    
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UW_InventoryGrid::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply ParentReply = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
	
	return FReply::Handled();
}