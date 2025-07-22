#include "W_InventoryGrid.h"
#include "W_Inventory.h"
#include "W_Combine.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryComponent.h"

void UW_InventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();
    
	SetIsFocusable(true);
	
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(0);
		CurrentTabIndex = 0;
	}
	
	if (UW_InventoryWidget)
	{
		UW_InventoryWidget->Items = Items;
		UW_InventoryWidget->InventorySize = InventorySize;
		UW_InventoryWidget->ActorItems = ActorItems;
		UW_InventoryWidget->ParentInventoryGrid = this;
	}
}

void UW_InventoryGrid::RefreshInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("InventoryGrid: RefreshInventory chamado"));
	
	if (UW_InventoryWidget)
	{
		UW_InventoryWidget->Items = Items;
		UW_InventoryWidget->InventorySize = InventorySize;
		UW_InventoryWidget->ActorItems = ActorItems;
		
		UW_InventoryWidget->ParentInventoryGrid = this;
		
		UE_LOG(LogTemp, Warning, TEXT("Referências reconfiguradas - ParentInventoryGrid: %s, HB_TopBar: %s"), 
			   UW_InventoryWidget->ParentInventoryGrid ? TEXT("Valid") : TEXT("NULL"),
			   (UW_InventoryWidget->ParentInventoryGrid && UW_InventoryWidget->ParentInventoryGrid->HB_TopBar) ? TEXT("Valid") : TEXT("NULL"));
		
		UW_InventoryWidget->RefreshInventory();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_InventoryWidget é nulo em RefreshInventory!"));
	}
}

void UW_InventoryGrid::SwitchToInventory()
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(0);
		CurrentTabIndex = 0;
		UE_LOG(LogTemp, Warning, TEXT("Switched to Inventory tab"));
	}
}

void UW_InventoryGrid::SwitchToCombine()
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(1);
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