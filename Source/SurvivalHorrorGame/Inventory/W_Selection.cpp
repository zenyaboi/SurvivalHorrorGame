#include "W_Selection.h"
#include "S_ItemData.h"
#include "Slate/SGameLayerManager.h"

void UW_Selection::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_Selection::SetCurrentItem(const FItemData& ItemData)
{
	CurrentItemData = ItemData;
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

void UW_Selection::BindCombineButtonEvent(UButton* Button)
{
	if (!Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("Botão não encontrado buaaa"));
		return;
	}

	BTN_Combine = Button;

	BTN_Combine->OnClicked.AddDynamic(this, &UW_Selection::OnCombineButtonClicked);
	UE_LOG(LogTemp, Warning, TEXT("Botão encontrado e binded wahooo"));
}

void UW_Selection::OnCombineButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("APERTADO COM SUCESSO :D"));

	TriggerCombineEvent();
}

void UW_Selection::TriggerCombineEvent()
{
	OnCombineEvent.Broadcast(CurrentItemData);
	UE_LOG(LogTemp, Warning, TEXT("PARE"));

	CombineItem(CurrentItemData);
}

void UW_Selection::CombineItem(const FItemData& ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("weed"));
}

void UW_Selection::BindInspectButtonEvent(UButton* Button)
{
	if (!Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("Botão não encontrado buaaa"));
		return;
	}

	BTN_Inspect = Button;

	BTN_Inspect->OnClicked.AddDynamic(this, &UW_Selection::OnInspectButtonClicked);
	UE_LOG(LogTemp, Warning, TEXT("Botão encontrado e binded wahooo"));
}

void UW_Selection::OnInspectButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("APERTADO COM SUCESSO :D"));

	TriggerInspectEvent();
}

void UW_Selection::TriggerInspectEvent()
{
	OnInspectEvent.Broadcast(CurrentItemData);
	UE_LOG(LogTemp, Warning, TEXT("PARE"));

	InspectItem(CurrentItemData);
}

void UW_Selection::InspectItem(const FItemData& ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("look at that shi man"));
}

void UW_Selection::BindDeleteButtonEvent(UButton* Button)
{
	if (!Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("Botão não encontrado buaaa"));
		return;
	}

	BTN_Delete = Button;

	BTN_Delete->OnClicked.AddDynamic(this, &UW_Selection::OnDeleteButtonClicked);
	UE_LOG(LogTemp, Warning, TEXT("Botão encontrado e binded wahooo"));
}

void UW_Selection::OnDeleteButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("APERTADO COM SUCESSO :D"));

	TriggerDeleteEvent();
}

void UW_Selection::TriggerDeleteEvent()
{
	APlayerController* PlayerController = GetOwningPlayer();
	
	OnDeleteEvent.Broadcast(PlayerController, CurrentItemData);
	UE_LOG(LogTemp, Warning, TEXT("PARE"));

	DeleteItem(PlayerController, CurrentItemData);
}

void UW_Selection::DeleteItem(APlayerController* PlayerControllerRef, FItemData CurrentItemRef)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerControllerRef->GetPawn());
	
	UE_LOG(LogTemp, Warning, TEXT("yah biiih"));
	if (!PlayerCharacter)
		return;

	UInventoryComponent* InvTarget = PlayerCharacter->GetInventoryComponent();
	int32 InvSize = InvTarget->InventorySize;
	int32 ItemIndex = InvTarget->Items.Find(CurrentItemRef);

	InvTarget->Items.RemoveAt(ItemIndex);
	InvTarget->Items.SetNum(InvSize);
	InvTarget->RefreshInventory();
}
