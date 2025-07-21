#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"
#include "SurvivalHorrorGame/Inventory/W_ItemSlot.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "InventoryComponent.h"
#include "Components/Border.h"

void UW_InventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();
    
	SetIsFocusable(true);

	ItemName->SetText(FText::GetEmpty());
	ItemDescription->SetText(FText::GetEmpty());
	
}

void UW_InventoryGrid::RefreshInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("RefreshInventory C++ executado"));
    
	if (!WrapBoxInventory)
	{
		UE_LOG(LogTemp, Error, TEXT("WrapBoxInventory não encontrado!"));
		return;
	}
    
	if (!SlotWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SlotWidgetClass não configurado!"));
		return;
	}
    
	WrapBoxInventory->ClearChildren();
    
	for (int32 i = 0; i < InventorySize; i++)
	{
		UW_ItemSlot* SlotWidget = CreateWidget<UW_ItemSlot>(GetWorld(), SlotWidgetClass);
        
		if (SlotWidget)
		{
			SlotWidget->SlotIndex = i;

			if (i < Items.Num())
			{
				SlotWidget->CurrentItem = Items[i];
				if (i < ActorItems.Num() && ActorItems[i])
				{
					SlotWidget->CurrentActorItem = ActorItems[i];
					UE_LOG(LogTemp, Warning, TEXT("Slot %d: Actor atribuído!"), i);
				}
				else
				{
					SlotWidget->CurrentActorItem = nullptr;
					UE_LOG(LogTemp, Warning, TEXT("Slot %d: Nenhum actor"), i);
				}
				SlotWidget->RefreshSlot();
			}
			else
			{
				SlotWidget->CurrentItem = FItemData();
				SlotWidget->CurrentActorItem = nullptr;
				SlotWidget->RefreshSlot();
			}

			SlotWidget->InventoryGrid = this;
			
			WrapBoxInventory->AddChild(SlotWidget);
			UE_LOG(LogTemp, Warning, TEXT("Slot %d criado"), i);
		}
	}
}

FReply UW_InventoryGrid::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
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