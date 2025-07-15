#include "SurvivalHorrorGame/Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isInnerOverlapped = false;
	isOuterOverlapped = false;

	iconLocation = FVector(0, 0, 30);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<USphereComponent*> Spheres;
	GetComponents<USphereComponent>(Spheres);
	
	for (USphereComponent* Sphere : Spheres)
	{
		if (Sphere->GetName().Contains(TEXT("inner")))
			InnerSphere = Sphere;
		else if (Sphere->GetName().Contains(TEXT("outer")))
			OuterSphere = Sphere;
	}
	
	TArray<UBillboardComponent*> Icons;
	GetComponents<UBillboardComponent>(Icons);
	
	for (UBillboardComponent* Icon : Icons)
	{
		if (Icon->GetName().Contains(TEXT("inner")))
			InnerIcon = Icon;
		else if (Icon->GetName().Contains(TEXT("outer")))
			OuterIcon = Icon;
	}
	
	if (InnerIcon)
	{
		InnerIcon->SetVisibility(false);
		InnerIcon->SetRelativeLocation(iconLocation);
	}
	if (OuterIcon)
	{
		OuterIcon->SetVisibility(false);
		OuterIcon->SetRelativeLocation(iconLocation);
	}
	
	if (InnerSphere)
	{
		InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnInnerBeginOverlap);
		InnerSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnInnerEndOverlap);
	}
	
	if (OuterSphere)
	{
		OuterSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOuterBeginOverlap);
		OuterSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnOuterEndOverlap);
	}
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isInnerOverlapped || !isOuterOverlapped) OuterIcon->SetVisibility(false);
	else if (!isInnerOverlapped || isOuterOverlapped) OuterIcon->SetVisibility(true);
}

void ABaseItem::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Inner Sphere Begin Overlap with: %s"), *OtherActor->GetName());

	isInnerOverlapped = true;
	
	if (InnerIcon) 
	{
		InnerIcon->SetVisibility(true);
		UE_LOG(LogTemp, Warning, TEXT("Inner Icon mostrado"));
	}
}

void ABaseItem::OnInnerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Inner Sphere End Overlap with: %s"), *OtherActor->GetName());

	isInnerOverlapped = false;
	
	if (InnerIcon) 
	{
		InnerIcon->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Inner Icon escondido"));
	}
}

void ABaseItem::OnOuterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Outer Sphere Begin Overlap with: %s"), *OtherActor->GetName());

	isOuterOverlapped = true;	
	
	if (OuterIcon) 
	{
		OuterIcon->SetVisibility(true);
		UE_LOG(LogTemp, Warning, TEXT("Outer Icon mostrado"));
	}
}

void ABaseItem::OnOuterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Outer Sphere End Overlap with: %s"), *OtherActor->GetName());

	isOuterOverlapped = false;
	
	if (OuterIcon) 
	{
		OuterIcon->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Outer Icon escondido"));
	}
}