#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteract : public UInterface
{
	GENERATED_BODY()
};

class SURVIVALHORRORGAME_API IInteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool Interact(ACharacter* Interactor);
	virtual bool Interact_Implementation(ACharacter* Interactor) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inspect")
	void Inspect(APlayerController* Interactor, UStaticMesh* ItemMesh, const FText& ItemName, const FText& ItemDescription, UW_Inventory* InventoryRef);
	virtual void Inspect_Implementation(APlayerController* Interactor, UStaticMesh* ItemMesh,
		const FText& ItemName, const FText& ItemDescription, UW_Inventory* InventoryRef) = 0;
};
