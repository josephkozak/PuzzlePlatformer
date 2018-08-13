                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     // Fill out your copyright notice in the Description page of Project Settings.

#include "MenuUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "PuzzlePlatformerGameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "MenuSystem/ServerRow.h"
#include "UObject/ConstructorHelpers.h"

UMenuUserWidget::UMenuUserWidget(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget>  TextBlockWidgetClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));

	UE_LOG(LogTemp, Warning, TEXT("Constructed GameInstance"));

	if (!ensure(TextBlockWidgetClass.Class != nullptr)) return;


	TextBlockClass = TextBlockWidgetClass.Class;

}

void UMenuUserWidget::SetServerList(TArray<FServerInfo> Servers)
{

	if (!ensure(ServerAddresses != nullptr)) return;

	ServerAddresses->ClearChildren();

	UWorld* World = this->GetWorld();

	if (!ensure(World != nullptr)) return;

	uint32 i = 0;
	for (const FServerInfo& Server : Servers) {

		UServerRow* NewRow = CreateWidget<UServerRow>(World, TextBlockClass);
		if (!ensure(NewRow != nullptr)) return;

		FString SName = FString(Server.ServerName).Mid(0, 20);
		FString PName = FString(Server.HostingPlayerName).Mid(0, 10);

		FText PlayerCount = FText::FromString(FString::Printf(TEXT("%d/%d"), Server.NumPlayers, Server.MaxPlayers));

		NewRow->SetRowText(SName, PName, PlayerCount);
		NewRow->Setup(this, i);

		++i;

		ServerAddresses->AddChild(NewRow);

	}

}

void UMenuUserWidget::SelectIndex(uint32 Index)
{

	SelectedIndex = Index;
	UpdateChildren();

}

bool UMenuUserWidget::Initialize()
{

	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnHostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnJoinButtonClicked);

	BackButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnBackButtonClicked);
	HostBack->OnClicked.AddDynamic(this, &UMenuUserWidget::OnBackButtonClicked);

	QuitButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnQuitButtonClicked);

	JoinServer->OnClicked.AddDynamic(this, &UMenuUserWidget::OnJoinServerButtonClicked);
	RefreshButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnRefreshButtonClicked);

	CreateGame->OnClicked.AddDynamic(this, &UMenuUserWidget::OnCreateGameButtonClicked);




	return true;
}

void UMenuUserWidget::OnHostButtonClicked()
{

	MenuSwitcher->SetActiveWidget(HostMenu);



}

void UMenuUserWidget::OnCreateGameButtonClicked()
{

	if (MenuInterface != nullptr) {

		MenuInterface->Host(ServerName->GetText());

	}
	else {


		UE_LOG(LogTemp, Warning, TEXT("Menu Interface is NULL !!"));

	}

	UE_LOG(LogTemp, Warning, TEXT("Hosting game.."));


}

void UMenuUserWidget::OnJoinServerButtonClicked()
{

	if (SelectedIndex.IsSet() && MenuInterface != nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("Joining at index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());

	} else {

		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));

	}

}

void UMenuUserWidget::UpdateChildren()
{

	for (int i = 0; i < ServerAddresses->GetChildrenCount(); i++) {

		UServerRow* SelectedRow = Cast<UServerRow>(ServerAddresses->GetChildAt(i));
		if (SelectedRow) {

			SelectedRow->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);

			/*if (i == SelectedIndex) {

				SelectedRow->Selected = true;

			} else {

				SelectedRow->Selected = false;

			}*/

		}


	}



}

void UMenuUserWidget::OnJoinButtonClicked() {



	//SetServerList(MenuInterface->GetServerList());
	MenuSwitcher->SetActiveWidget(JoinMenu);


}

void UMenuUserWidget::OnBackButtonClicked()
{

	MenuSwitcher->SetActiveWidget(this);

}

void UMenuUserWidget::OnQuitButtonClicked()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	PC->ConsoleCommand("quit", true);

}

void UMenuUserWidget::OnRefreshButtonClicked()
{

	MenuInterface->RefreshServerList();

}
