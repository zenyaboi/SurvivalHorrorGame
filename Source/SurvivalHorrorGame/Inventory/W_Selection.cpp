#include "W_Selection.h"
#include "S_ItemData.h"

void UW_Selection::NativeConstruct()
{
	Super::NativeConstruct();

}

void UW_Selection::BindHealButtonEvent(UButton* Button)
{
	if (!Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("Botão não encontrado buaaa"));
		return;
	}

	BTN_Heal = Button;

	BTN_Heal->OnClicked.AddDynamic(this, &UW_Selection::OnHealButtonClicked);
	UE_LOG(LogTemp, Warning, TEXT("Botão encontrado e binded wahooo"));
}

void UW_Selection::OnHealButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("APERTADO COM SUCESSO :D"));

	TriggerHealEvent();
}

void UW_Selection::TriggerHealEvent()
{
	OnHealEvent.Broadcast(CurrentItemData);
	UE_LOG(LogTemp, Warning, TEXT("aaaaaaaaaaaaaaaaaaaaaa"));

	HealPlayer(CurrentItemData);
}

void UW_Selection::HealPlayer(const FItemData& ItemData)
{
	if (!ItemData.isItemHealable)
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT A HEAL BITCH"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("IT IS A HEAL BITCH"));
}

void UW_Selection::SetCurrentItem(const FItemData& ItemData)
{
	CurrentItemData = ItemData;
}