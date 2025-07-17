#pragma once

#include "CoreMinimal.h"
#include "W_ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "W_Selection.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealEvent, FItemData, Item);

UCLASS()
class SURVIVALHORRORGAME_API UW_Selection : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	class UButton* BTN_Heal;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData CurrentItemData;

	UFUNCTION()
	void OnHealButtonClicked();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	FOnHealEvent OnHealEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void BindHealButtonEvent(UButton* Button);
	
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerHealEvent();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void HealPlayer(const FItemData& ItemData);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetCurrentItem(const FItemData& ItemData);
};
