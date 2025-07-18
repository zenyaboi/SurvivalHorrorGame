// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectItem.h"

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
	
}

// Called every frame
void AInspectItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInspectItem::Inspect_Implementation(ACharacter* Interactor, UStaticMesh* ItemMesh,
										const FText& ItemName, const FText& ItemDescription, 
										UW_InventoryGrid* InventoryRef)
{
	UE_LOG(LogTemp, Warning, TEXT("A"));
}

bool AInspectItem::Interact_Implementation(ACharacter* Interactor)
{
	return false;
}

