#include "SurvivalHorrorGame/Inventory/InventoryComponent.h"
#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InventorySize = 12;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (WInventoryGridClass)
	{
		InventoryReference = CreateWidget<UUserWidget>(GetWorld(), WInventoryGridClass);

		if (UW_InventoryGrid* InventoryGrid = Cast<UW_InventoryGrid>(InventoryReference))
		{
			InventoryGrid->Items = Items;
			InventoryGrid->InventorySize = InventorySize;
		}
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

