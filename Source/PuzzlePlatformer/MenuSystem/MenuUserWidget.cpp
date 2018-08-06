                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     // Fill out your copyright notice in the Description page of Project Settings.

#include "MenuUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "PuzzlePlatformerGameInstance.h"
#include "Components/WidgetSwitcher.h"



bool UMenuUserWidget::Initialize()
{

	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnHostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnJoinButtonClicked);
	BackButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnBackButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnQuitButtonClicked);
	JoinServer->OnClicked.AddDynamic(this, &UMenuUserWidget::OnJoinServerButtonClicked);


	return true;
}

void UMenuUserWidget::OnHostButtonClicked()
{

	if (MenuInterface != nullptr) {

		MenuInterface->Host();

	}
	else {


		UE_LOG(LogTemp, Warning, TEXT("Menu Interface is NULL !!"));

	}

	UE_LOG(LogTemp, Warning, TEXT("Hosting game.."));



}

void UMenuUserWidget::OnJoinServerButtonClicked()
{

	if (MenuInterface != nullptr) {

		MenuInterface->Join(IPAddress->Text.ToString());

	} else {


		UE_LOG(LogTemp, Warning, TEXT("Menu Interface is NULL !!"));

	}

	UE_LOG(LogTemp, Warning, TEXT("Joining Game..."));


}

void UMenuUserWidget::OnJoinButtonClicked() {

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
