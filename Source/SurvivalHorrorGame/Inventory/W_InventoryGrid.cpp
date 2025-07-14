#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"
#include "SurvivalHorrorGame/Inventory/W_ItemSlot.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"


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
				SlotWidget->RefreshSlot();
			}
			else
			{
				SlotWidget->CurrentItem = FItemData();
				SlotWidget->RefreshSlot();
			}
			
			WrapBoxInventory->AddChild(SlotWidget);
			UE_LOG(LogTemp, Warning, TEXT("Slot %d criado"), i);
		}
	}
}