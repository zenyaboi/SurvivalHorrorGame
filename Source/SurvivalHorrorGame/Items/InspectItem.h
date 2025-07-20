#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalHorrorGame/Interfaces/Interact.h"
#include "W_Inspect.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "Components/SceneCaptureComponent2D.h"
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
	virtual void Inspect_Implementation(APlayerController* Interactor, UStaticMesh* ItemMesh,
		const FText& ItemName, const FText& ItemDescription, UW_InventoryGrid* InventoryRef) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* InspectRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WInspectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UW_Inspect* InspectWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UW_InventoryGrid* Inventory;

	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	bool bRotate = false;

	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	FRotator InitialRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	float CurrentFOV = 50.0f;

	UFUNCTION(BlueprintCallable, Category = "Inspection")
	void SetInspectRotation(FRotator ItemRotation);

	UFUNCTION(BlueprintCallable, Category = "Inspection") 
	void SetInspectScale(FVector InspectionScale);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool isInspectVisible;
	
};
