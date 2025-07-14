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
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
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