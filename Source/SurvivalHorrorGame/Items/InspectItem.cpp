#include "InspectItem.h"
#include "Blueprint/UserWidget.h"
#include "W_Inspect.h"
#include "Components/StaticMeshComponent.h"
#include "SurvivalHorrorGame/Inventory/W_InventoryGrid.h"

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

	USceneCaptureComponent2D* SceneCaptureComponent = FindComponentByClass<USceneCaptureComponent2D>();
	if (SceneCaptureComponent)
	{
		SceneCapture = SceneCaptureComponent;
		SceneCapture->FOVAngle = CurrentFOV;
	}

	UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (MeshComponent && MeshComponent->GetName().Contains(TEXT("Mesh")))
	{
		InitialRotation = MeshComponent->GetRelativeRotation();
		Item = MeshComponent;
	}

	if (WInspectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("YIIIPEEEE :)"));
		InspectRef = CreateWidget<UUserWidget>(GetWorld(), WInspectClass);
		InspectWidget = Cast<UW_Inspect>(InspectRef);
		if (InspectWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("YIIIPEEEE :)"));
			InspectWidget->InspectItemRef = this;
		}
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
	
	// Rotating item on the Z axis
	if (Rotate && IsLeftMousePressed && Item)
	{
		// Using mouse X axis to rotate the Z axis
		float XAxisValue = MouseInputX * -3.f * DeltaTime * 30.f;
		float YAxisValue = MouseInputY * -3.f * DeltaTime * 30.f;

		// Using Quaternions to "bypass" Gimbal Lock 
		FQuat YawRotation = FQuat(FVector::UpVector, FMath::DegreesToRadians(XAxisValue));
		FQuat PitchRotation = FQuat(FVector::LeftVector, FMath::DegreesToRadians(YAxisValue));

		FQuat CurrentQuat = Item->GetComponentTransform().GetRotation();
		FQuat NewQuat = YawRotation * PitchRotation * CurrentQuat;
		
		Item->SetWorldRotation(NewQuat);
		MouseInputX = 0.0f;
		MouseInputY = 0.0f;
	}
}

void AInspectItem::ReceiveMouseInput(float MouseDeltaX, float MouseDeltaY)
{
	MouseInputX = MouseDeltaX;
	MouseInputY = MouseDeltaY;
}

void AInspectItem::HandleLeftMousePressed()
{
	IsLeftMousePressed = true;
	Rotate = true;
}

void AInspectItem::HandleLeftMouseReleased()
{
	IsLeftMousePressed = false;
	Rotate = false;
}

void AInspectItem::HandleRightMousePressed()
{
	IsRightMousePressed = true;
	if (Item)
	{
		Item->SetRelativeRotation(InitialRotation);
	}
	if (SceneCapture)
	{
		SceneCapture->FOVAngle = 80.f;
		CurrentFOV = 80.f;
	}
}

void AInspectItem::HandleRightMouseReleased()
{
	IsRightMousePressed = false;
}

void AInspectItem::HandleMouseWheelScrollUp()
{
	CurrentFOV += 5.f;
	CurrentFOV = FMath::Clamp(CurrentFOV, 60.f, 110.f);
	if (SceneCapture)
	{
		SceneCapture->FOVAngle = CurrentFOV;
	}
}

void AInspectItem::HandleMouseWheelScrollDown()
{
	CurrentFOV -= 5.f;
	CurrentFOV = FMath::Clamp(CurrentFOV, 60.f, 110.f);
	if (SceneCapture)
	{
		SceneCapture->FOVAngle = CurrentFOV;
	}
}

void AInspectItem::CloseInspect(APlayerController* PlayerController)
{
	if (InspectWidget)
	{
		InspectWidget->RemoveFromParent();
		InspectWidget = nullptr;
	}
	
	if (PlayerController)
	{
		PlayerController->EnableInput(PlayerController);
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetIgnoreMoveInput(false);
	}
	
	Destroy();
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
		Item->SetRelativeScale3D(FVector(0.5f));
		InspectWidget->ItemName->SetText(ItemName);
		InspectWidget->ItemDescription->SetText(ItemDescription);
		InspectWidget->AddToViewport();
		InspectWidget->InventoryGrid = InventoryRef;
		InspectWidget->InventoryGrid->HB_TopBar->SetVisibility(ESlateVisibility::Visible);

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

void AInspectItem::OnLeftMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("A"));
	Rotate = true;
}

void AInspectItem::OnLeftMouseReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("B"));
	Rotate = false;
}

void AInspectItem::OnRightMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("C"));
	Item->SetRelativeRotation(InitialRotation);
	SceneCapture->FOVAngle = 80.f;
}

void AInspectItem::OnRightMouseReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("D"));
}

void AInspectItem::OnMouseWheelScrollUp()
{
	UE_LOG(LogTemp, Warning, TEXT("E"));
	CurrentFOV += 1.f;
	CurrentFOV = FMath::Clamp(CurrentFOV, 60.f, 110.f);
	SceneCapture->FOVAngle = CurrentFOV;
}

void AInspectItem::OnMouseWheelScrollDown()
{
	UE_LOG(LogTemp, Warning, TEXT("F"));
	CurrentFOV -= 1.f;
	CurrentFOV = FMath::Clamp(CurrentFOV, 60.f, 110.f);
	SceneCapture->FOVAngle = CurrentFOV;
}

void AInspectItem::SetInspectRotation(FRotator ItemRotation)
{
	Item->SetRelativeRotation(ItemRotation);
}

void AInspectItem::SetInspectScale(FVector InspectionScale)
{
	Item->SetRelativeScale3D(InspectionScale);
}

bool AInspectItem::Interact_Implementation(ACharacter* Interactor)
{
	return false;
}