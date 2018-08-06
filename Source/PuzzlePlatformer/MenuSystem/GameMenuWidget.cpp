// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenuWidget.h"
#include "Components/Button.h"

void UGameMenuWidget::OnQuitButtonClicked()
{

	this->RemoveFromViewport();

	UWorld* World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	if (PlayerController->Role != ROLE_Authority) {

		DestroyMenu();
		return;

	}


	MenuInterface->BackToMenu();


}

void UGameMenuWidget::OnCancelButtonClicked()
{

	DestroyMenu();

}

bool UGameMenuWidget::Initialize()
{

	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(QuitButton != nullptr)) return false;
	if (!ensure(CancelButton != nullptr)) return false;


	QuitButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnQuitButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UGameMenuWidget::OnCancelButtonClicked);

	return true;

}
