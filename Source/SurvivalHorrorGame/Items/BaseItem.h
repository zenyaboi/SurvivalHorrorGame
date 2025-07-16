#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalHorrorGame/Interfaces/Interact.h"
#include "SurvivalHorrorGame/Inventory/S_ItemData.h"
#include "BaseItem.generated.h"

UCLASS()
class SURVIVALHORRORGAME_API ABaseItem : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class USphereComponent* InnerSphere;
	
	UPROPERTY()
	class USphereComponent* OuterSphere;
	
	UPROPERTY()
	class UBillboardComponent* InnerIcon;
	
	UPROPERTY()
	class UBillboardComponent* OuterIcon;

	UFUNCTION()
	void OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnInnerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnOuterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOuterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool isInnerOverlapped;
	bool isOuterOverlapped;
	float iconZPosition;

	virtual bool Interact_Implementation(ACharacter* Interactor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem|Inventory")
	FItemData Item;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Item Mesh Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem|Mesh")
	FVector ItemScale;
	// Item Inspect Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem|Inspect")
	bool isInspect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem|Inspect")
	FRotator itemInspectionRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem|Inspect")
	FVector itemInspectionScale;
	// Item Setting Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem")
	FVector iconLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItem")
	bool isDebug;

	UFUNCTION(BlueprintCallable, Category = "BaseItem|Inventory")
	void BreakItemDataBlueprint(FText& Name, FText& Description, bool& Stackable, 
							   int32& Amount, UStaticMesh*& Mesh, UTexture2D*& Image, 
							   bool& Healable, int32& HealAmount);
};