// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalHorrorGame/Interfaces/Interact.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "InspectItem.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API AInspectItem : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInspectItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool Interact_Implementation(ACharacter* Interactor) override;
	virtual void Inspect_Implementation(ACharacter* Interactor, UStaticMesh* ItemMesh,
		const FText& ItemName, const FText& ItemDescription, UW_InventoryGrid* InventoryRef) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
