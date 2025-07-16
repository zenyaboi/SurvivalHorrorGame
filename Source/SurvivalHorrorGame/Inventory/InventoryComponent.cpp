#include "SurvivalHorrorGame/Inventory/InventoryComponent.h"
#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InventorySize = 12;

	isInventoryVisible = false;
	maxStack = 30;
	currentStack = 0;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (WInventoryGridClass)
	{
		InventoryReference = CreateWidget<UUserWidget>(GetWorld(), WInventoryGridClass);

		UW_InventoryGrid* InventoryGrid = Cast<UW_InventoryGrid>(InventoryReference);
		if (InventoryGrid)
		{
			InventoryGrid->Items = Items;
			InventoryGrid->InventorySize = InventorySize;
			RefreshInventory();
		}
	}
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::RefreshInventory()
{
	if (UW_InventoryGrid* InventoryGrid = Cast<UW_InventoryGrid>(InventoryReference))
	{
		InventoryGrid->Items = Items;
		InventoryGrid->InventorySize = InventorySize;
		InventoryGrid->RefreshInventory();
	}
}

void UInventoryComponent::ToggleInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("InventoryComponent::ToggleInventory chamado!"));
	
	if (!InventoryReference)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryReference é NULL! Widget não foi criado."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryReference encontrado!"));
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController não encontrado!"));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerController encontrado!"));

	isInventoryVisible = !isInventoryVisible;
	UE_LOG(LogTemp, Warning, TEXT("bIsInventoryVisible = %s"), isInventoryVisible ? TEXT("True") : TEXT("False"));
	if (isInventoryVisible)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tentando adicionar widget à viewport..."));
		InventoryReference->AddToViewport();
		
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(InventoryReference->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;

		InventoryReference->SetKeyboardFocus();
		UE_LOG(LogTemp, Warning, TEXT("Widget adicionado e input mode configurado!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tentando remover widget da viewport..."));
		InventoryReference->RemoveFromParent();
		
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
		UE_LOG(LogTemp, Warning, TEXT("Widget removido e input mode revertido!"));
	}
}

FAddItemResult UInventoryComponent::AddItemToInventory(ABaseItem* Item)
{
	FAddItemResult Result;
	FStackCheckResult shouldStack;
	
	if (!IsValid(Item))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item inválido"));
		return Result;
	}
	
	FItemData InteractedItem = Item->GetItemDataConstRef();

	if (!InteractedItem.isItemInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item não é para inventário"));
		Result.WasAdded = false;
		return Result;
	}
	
	int32 CurrentIndex = 0;
	for (int32 i =0; i < Items.Num(); i++)
	{
		FItemData& CurrentItem = Items[i];
		CurrentIndex = i;

		UE_LOG(LogTemp, Warning, TEXT("Current index: %d"), CurrentIndex);

		shouldStack = ShouldStackItems(CurrentItem, InteractedItem);
		UE_LOG(LogTemp, Warning, TEXT("Is Stackable: %hhd"), shouldStack.CanStack);

		if (shouldStack.CanStack)
		{
			CurrentItem.ItemAmount = shouldStack.NewQuantity;

			Result.WasAdded = true;
			Result.TargetSlotIndex = CurrentIndex;
			Result.WasStacked = true;
			Result.FinalQuantity = shouldStack.NewQuantity;

			RefreshInventory();
			UE_LOG(LogTemp, Warning, TEXT("Item empilhado no índice %d com quantidade %d"), CurrentIndex, shouldStack.NewQuantity);
			return Result;
		}
		else
		{
			bool spaceInInv = hasSpaceInventory(shouldStack.NewQuantity);
			if (spaceInInv)
			{
				
			}
		}
	}
}

FStackCheckResult UInventoryComponent::ShouldStackItems(FItemData itemFromInv, FItemData itemCurrentActor)
{
	FStackCheckResult Result;

	// Checking if current item is supposed to go to inv
	if (!itemCurrentActor.isItemInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item not supposed for inventory"));
		Result.CanStack = false;
		return Result;
	}
	
	// Checking if both item names are the same
	if (!itemFromInv.ItemName.EqualTo(itemCurrentActor.ItemName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not same name"));
		Result.CanStack = false;
		return Result;
	}

	// Checking if item is stackable
	if (!itemCurrentActor.isItemStackable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item can't stack"));
		Result.CanStack = false;
		return Result;
	}

	// Checking stack amount
	currentStack = itemCurrentActor.ItemAmount + itemFromInv.ItemAmount;
	if (currentStack > maxStack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Too much shit"));
		Result.CanStack = false;
		Result.NewQuantity = maxStack;
		Result.ReachedMaxStack = true;
		return Result;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item in inventory"));
		Result.CanStack = true;
		Result.NewQuantity = currentStack;
		Result.ReachedMaxStack = false;
		
		return Result;
	}
}

bool UInventoryComponent::hasSpaceInventory(int32 amountInInv)
{
	if (amountInInv != 0)
	{
		return false;
	}

	return true;
}
