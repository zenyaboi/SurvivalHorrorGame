#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalHorrorGame/Inventory/InventoryComponent.h"
#include "SurvivalHorrorGame/UI/W_HUD.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere);
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere);
	class USpringArmComponent* FlashlightBoom;
	UPROPERTY(EditAnywhere);
	class UInventoryComponent* InventoryComponent;

	// Keyboard Input Movement
	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void Run();
	void ToggleCrouch();

	// Camera Mouse Input 
	void Turn(float InputValue);
	void Look(float InputValue);

	// Misc
	void FlashlightToggle();
	void ToggleInventory();
	void Interact();

	// UI Functions
	void CreateHUDWidget();
public:
	// Camera Sensitivity
	UPROPERTY(EditAnywhere, Category = Camera);
	float HorizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = Camera);
	float VerticalSensitivity;

	// Widget References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI");
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UW_HUD* HUDWidget;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
protected:
	float WalkSpeed;
	float RunningSpeed;
	float CrouchSpeed;

	float TargetCapsuleHalfHeight;
	float CurrentCapsuleHalfHeight;
	float CapsuleInterpSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement");
	bool isRunning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement");
	bool isCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flashlight");
	bool isFlashlightOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange;

	FTimerHandle InteractionTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction");
	bool isInteracting;

	void ResetInteractionState();
public:
	UPROPERTY(EditAnywhere);
	class USpotLightComponent* Flashlight;
};
