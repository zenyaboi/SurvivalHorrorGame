#include "SurvivalHorrorGame/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurvivalHorrorGame/Interfaces/Interact.h"
#include "SurvivalHorrorGame/Inventory/InventoryComponent.h"
#include "SurvivalHorrorGame/UI/W_HUD.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	// Setting Inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	// Player Speed
	WalkSpeed = 200.0f;
	RunningSpeed = 300.0f;
	CrouchSpeed = 120.0f;

	isRunning = false;
	isCrouching = false;
	
	// Camera Sensitivity
	HorizontalSensitivity = 0.5f;
	VerticalSensitivity = 0.5f;

	// Crouch Settings
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().AgentRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	GetCharacterMovement()->GetNavAgentPropertiesRef().AgentHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f;
	CurrentCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	TargetCapsuleHalfHeight = CurrentCapsuleHalfHeight;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	FlashlightBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FlashlightBoom"));
	FlashlightBoom->SetupAttachment(Camera);
	FlashlightBoom->TargetArmLength = 0.f;
	FlashlightBoom->bUsePawnControlRotation = true;
	FlashlightBoom->bEnableCameraRotationLag = true;
	FlashlightBoom->CameraRotationLagSpeed = 20.f;
	FlashlightBoom->bDoCollisionTest = false;
	
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FlashlightBoom);
	isFlashlightOn = false;

	HUDWidget = nullptr;

	InteractionRange = 300.0f;
	
	isInteracting = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateHUDWidget();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentCapsuleHalfHeight = FMath::FInterpTo(CurrentCapsuleHalfHeight, TargetCapsuleHalfHeight, DeltaTime, CapsuleInterpSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(CurrentCapsuleHalfHeight);

	Flashlight->SetVisibility(isFlashlightOn);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Player Movement Input
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this,  &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::ToggleCrouch);

	// Camera Input
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::Look);

	// Misc
	PlayerInputComponent->BindAction("FlashlightToggle", IE_Pressed, this, &APlayerCharacter::FlashlightToggle);
	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APlayerCharacter::ToggleInventory);
	PlayerInputComponent->BindAction("InteractKey", IE_Pressed, this,  &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void APlayerCharacter::Run()
{
	isRunning = !isRunning;

	if (!isCrouching)
	{
		float velocity = isRunning ? RunningSpeed : WalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = velocity;
	}
}

void APlayerCharacter::ToggleCrouch()
{
	isCrouching = !isCrouching;
	if (isCrouching)
	{
		TargetCapsuleHalfHeight = 44.f;
		isRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
	}
	else
	{
		TargetCapsuleHalfHeight = 88.f;
		GetCharacterMovement()->MaxWalkSpeed = isRunning ? RunningSpeed : WalkSpeed;;
	}
}

void APlayerCharacter::Turn(float InputValue)
{
	AddControllerYawInput(InputValue * HorizontalSensitivity);
}

void APlayerCharacter::Look(float InputValue)
{
	AddControllerPitchInput(InputValue * VerticalSensitivity);
}

void APlayerCharacter::FlashlightToggle()
{
	isFlashlightOn = !isFlashlightOn;
}

void APlayerCharacter::ToggleInventory()
{
	if (InventoryComponent)
	{
		InventoryComponent->ToggleInventory();
	}
}

void APlayerCharacter::Interact()
{
	if (isInteracting)
	{
		return;
	}
	
	FVector CameraLocation = Camera->GetComponentLocation();
	FVector CameraForward = Camera->GetForwardVector();

	FVector EndLocation = CameraLocation + (CameraForward * InteractionRange);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	FHitResult HitResult;
	bool hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CameraLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);

	if (hit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Interagindo com: %s"), *HitActor->GetName());
			IInteract* InteractInterface = Cast<IInteract>(HitActor);
			if (InteractInterface)
			{
				bool InteractionResult = IInteract::Execute_Interact(HitActor, this);
				if (InteractionResult)
				{
					isInteracting = true;

					GetWorld()->GetTimerManager().SetTimer(
						InteractionTimerHandle,
						this,
						&APlayerCharacter::ResetInteractionState,
						1.0f,
						false
					);
				}
			}
			else
			{
				isInteracting = false;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nenhum objeto encontrado"));
	}

	// Debug
	#if WITH_EDITOR
		if (hit)
		{
			DrawDebugLine(GetWorld(), CameraLocation, HitResult.Location, FColor::Green, false, 5.0f, 0, 2.0f);
			DrawDebugSphere(GetWorld(), HitResult.Location, 5.0f, 12, FColor::Red, false, 5.0f);
		}
		else
		{
			DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Red, false, 5.0f, 0, 2.0f);
		}
	#endif
}

void APlayerCharacter::ResetInteractionState()
{
	isInteracting = false;
	UE_LOG(LogTemp, Warning, TEXT("Interação resetada"));
}

void APlayerCharacter::CreateHUDWidget()
{
	if (HUDWidgetClass && !HUDWidget)
	{
		HUDWidget = CreateWidget<UW_HUD>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}