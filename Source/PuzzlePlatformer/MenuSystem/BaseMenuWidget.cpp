// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMenuWidget.h"

bool UBaseMenuWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	return true;
}

void UBaseMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{


	this->MenuInterface = MenuInterface;

	if (this->MenuInterface == nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("MENU INTEFACE IS NULL ON SET"));

	}

}

void UBaseMenuWidget::Setup()
{

	this->AddToViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();


	if (!ensure(PlayerController != nullptr)) return;



	FInputModeUIOnly InputData;
	InputData.SetWidgetToFocus(this->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);


	PlayerController->bShowMouseCursor = true;
	//FInputModeDataBase
	PlayerController->SetInputMode(InputData);

	if (MenuInterface == nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("MENU INTEFACE IS NULL ON SET"));

	}



}

void UBaseMenuWidget::DestroyMenu()
{

	this->RemoveFromViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();


	if (!ensure(PlayerController != nullptr)) return;



	FInputModeGameOnly InputData;

	PlayerController->bShowMouseCursor = false;
	//FInputModeDataBase
	PlayerController->SetInputMode(InputData);

}

void UBaseMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{

	this->RemoveFromViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();


	if (!ensure(PlayerController != nullptr)) return;



	FInputModeGameOnly InputData;

	PlayerController->bShowMouseCursor = false;
	//FInputModeDataBase
	PlayerController->SetInputMode(InputData);



}



