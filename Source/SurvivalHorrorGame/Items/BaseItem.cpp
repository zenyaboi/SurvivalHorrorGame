#include "SurvivalHorrorGame/Items/BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating Cube Mesh (assign as Cube on BP)
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	//Creating Sphere Collisions
	OuterSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereCollision"));
	OuterSphereCollision->SetupAttachment(RootComponent);
	OuterSphereCollision->SetSphereRadius(57.f);
	OuterSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OuterSphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	OuterSphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OuterSphereCollision->SetGenerateOverlapEvents(true);
	
	InnerSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereCollision"));
	InnerSphereCollision->SetupAttachment(RootComponent);
	InnerSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InnerSphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InnerSphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InnerSphereCollision->SetGenerateOverlapEvents(true);

	// Creating Billboards
	InnerInteractIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("InnerInteractIcon"));
	InnerInteractIcon->SetupAttachment(InnerSphereCollision);
	InnerInteractIcon->SetVisibility(false);
	InnerInteractIcon->SetHiddenInGame(false);
	
	OuterInteractIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("OuterInteractIcon"));
	OuterInteractIcon->SetupAttachment(OuterSphereCollision);
	OuterInteractIcon->SetVisibility(false);
	OuterInteractIcon->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

