#include "SurvivalHorrorGame/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurvivalHorrorGame/Inventory/InventoryComponent.h"

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
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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