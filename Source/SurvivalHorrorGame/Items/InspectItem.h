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

	// Interface Functions
	virtual bool Interact_Implementation(ACharacter* Interactor) override;
	virtual void Inspect_Implementation(APlayerController* Interactor, UStaticMesh* ItemMesh,
		const FText& ItemName, const FText& ItemDescription, UW_InventoryGrid* InventoryRef) override;

	// Components References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	USceneCaptureComponent2D* SceneCapture;

	// Inspect Widget References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* InspectRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WInspectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UW_Inspect* InspectWidget;

	// Inventory Widget Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UW_InventoryGrid* Inventory;

	// Rotation and Scale Variables
	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	bool Rotate = false;
	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	FRotator InitialRotation;
	UPROPERTY(BlueprintReadWrite, Category = "Inspection")
	float CurrentFOV = 50.0f;

	// Mouse Input Reference
	float MouseInputX;
	float MouseInputY;
	bool IsLeftMousePressed = false;
	bool IsRightMousePressed = false;

	// Mouse Input Functions
	void GetMouseInput();
	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void OnRightMousePressed();
	void OnRightMouseReleased();

	// Rotation and Scale Functions
	UFUNCTION(BlueprintCallable, Category = "Inspection")
	void SetInspectRotation(FRotator ItemRotation);
	UFUNCTION(BlueprintCallable, Category = "Inspection") 
	void SetInspectScale(FVector InspectionScale);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool isInspectVisible;
	
};
