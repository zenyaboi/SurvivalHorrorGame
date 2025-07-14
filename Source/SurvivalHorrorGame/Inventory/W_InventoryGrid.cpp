#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"
#include "Components/WrapBox.h"

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
		UUserWidget* SlotWidget = CreateWidget<UUserWidget>(GetWorld(), SlotWidgetClass);
        
		if (SlotWidget)
		{
			WrapBoxInventory->AddChild(SlotWidget);
			UE_LOG(LogTemp, Warning, TEXT("Slot %d criado"), i);
		}
	}
}