#include "InspectItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInspectItem::AInspectItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInspectItem::BeginPlay()
{
	Super::BeginPlay();

	isInspectVisible = false;

	TArray<UStaticMeshComponent*> StaticMeshes;
	GetComponents<UStaticMeshComponent>(StaticMeshes);

	for (UStaticMeshComponent* Mesh : StaticMeshes)
	{
		if (Mesh->GetName().Contains(TEXT("Mesh")))
			Item = Mesh;
	}

	if (WInspectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("YIIIPEEEE :)"));
		InspectRef = CreateWidget<UUserWidget>(GetWorld(), WInspectClass);
		InspectWidget = Cast<UW_Inspect>(InspectRef);
		if (InspectWidget)
			UE_LOG(LogTemp, Warning, TEXT("YIIIPEEEE :)"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AWWWWW :("));
	}
}

// Called every frame
void AInspectItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInspectItem::Inspect_Implementation(APlayerController* Interactor, UStaticMesh* ItemMesh,
										const FText& ItemName, const FText& ItemDescription, 
										UW_InventoryGrid* InventoryRef)
{
	UE_LOG(LogTemp, Warning, TEXT("A"));
	if (!InspectWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("OOPS NOT FOUND"));
		return;
	}

	Inventory = InventoryRef;
	
	isInspectVisible = !isInspectVisible;
	if (isInspectVisible)
	{
		Item->SetStaticMesh(ItemMesh);
		InspectWidget->ItemName->SetText(ItemName);
		InspectWidget->ItemDescription->SetText(ItemDescription);
		InspectWidget->AddToViewport();

		// Making sure the game know we are controlling the Inspect
		Interactor->DisableInput(Interactor);
		Interactor->SetIgnoreLookInput(true);
		Interactor->SetIgnoreMoveInput(true);
		EnableInput(Interactor);
	}
	else
	{
		InspectWidget->RemoveFromParent();
		InspectWidget = nullptr;
		Destroy();
	}
}

bool AInspectItem::Interact_Implementation(ACharacter* Interactor)
{
	return false;
}

