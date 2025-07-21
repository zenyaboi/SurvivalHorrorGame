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

	GetMouseInput();

	// Rotating item on the Z axis
	if (Rotate)
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
	}
}

void AInspectItem::GetMouseInput()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		float MouseDeltaX, MouseDeltaY;
		PlayerController->GetInputMouseDelta(MouseDeltaX, MouseDeltaY);

		MouseInputX = MouseDeltaX;
		MouseInputY = MouseDeltaY;

		bool bLeftPressed = PlayerController->IsInputKeyDown(EKeys::LeftMouseButton);
		bool bRightPressed = PlayerController->IsInputKeyDown(EKeys::RightMouseButton);

		if (bLeftPressed && !IsLeftMousePressed)
		{
			OnLeftMousePressed(); // Chamada quando pressionado
		}
		if (!bLeftPressed && IsLeftMousePressed)
		{
			OnLeftMouseReleased(); // Chamada quando solto
		}
        
		if (bRightPressed && !IsRightMousePressed)
		{
			OnRightMousePressed();
		}
		if (!bRightPressed && IsRightMousePressed)
		{
			OnRightMouseReleased();
		}

		IsLeftMousePressed = bLeftPressed;
		IsRightMousePressed = bRightPressed;
	}
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
	SceneCapture->FOVAngle = 50.f;
}

void AInspectItem::OnRightMouseReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("D"));
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

