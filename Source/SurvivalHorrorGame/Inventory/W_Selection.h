#pragma once

#include "CoreMinimal.h"
#include "W_ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "W_Selection.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealEvent, FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombineEvent, FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInspectEvent, FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeleteEvent, FItemData, Item);

UCLASS()
class SURVIVALHORRORGAME_API UW_Selection : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData CurrentItemData;

	// Heal Functionality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	UButton* BTN_Heal;
	UFUNCTION()
	void OnHealButtonClicked();

	// Combine Functionality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combine")
	UButton* BTN_Combine;
	UFUNCTION()
	void OnCombineButtonClicked();
	
	// Inspect Functionality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspect")
	UButton* BTN_Inspect;
	UFUNCTION()
	void OnInspectButtonClicked();
	
	// Delete Functionality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspect")
	UButton* BTN_Delete;
	UFUNCTION()
	void OnDeleteButtonClicked();
public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetCurrentItem(const FItemData& ItemData);

	// Heal Events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	FOnHealEvent OnHealEvent;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void BindHealButtonEvent(UButton* Button);
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerHealEvent();
	UFUNCTION(BlueprintCallable, Category = "Events")
	void HealPlayer(const FItemData& ItemData);

	// Combine Events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	FOnCombineEvent OnCombineEvent;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void BindCombineButtonEvent(UButton* Button);
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerCombineEvent();
	UFUNCTION(BlueprintCallable, Category = "Events")
	void CombineItem(const FItemData& ItemData);
	
	// Inspect Events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	FOnInspectEvent OnInspectEvent;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void BindInspectButtonEvent(UButton* Button);
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerInspectEvent();
	UFUNCTION(BlueprintCallable, Category = "Events")
	void InspectItem(const FItemData& ItemData);
	
	// Delete Events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	FOnDeleteEvent OnDeleteEvent;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void BindDeleteButtonEvent(UButton* Button);
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerDeleteEvent();
	UFUNCTION(BlueprintCallable, Category = "Events")
	void DeleteItem(const FItemData& ItemData);
};
