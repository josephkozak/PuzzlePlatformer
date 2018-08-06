// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformerGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MenuUserWidget.h"
#include "MenuSystem/GameMenuWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/BaseMenuWidget.h"

UPuzzlePlatformerGameInstance::UPuzzlePlatformerGameInstance(const FObjectInitializer & ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<UUserWidget>  MenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	ConstructorHelpers::FClassFinder<UUserWidget>  GameMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));


	UE_LOG(LogTemp, Warning, TEXT("Constructed GameInstance"));

	if (!ensure(MenuWidgetClass.Class != nullptr)) return;
	if (!ensure(GameMenuWidgetClass.Class != nullptr)) return;


	MenuClass = MenuWidgetClass.Class;
	GameMenuClass = GameMenuWidgetClass.Class;

}

void UPuzzlePlatformerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance INIT"));
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *GameMenuClass->GetName());




}


void UPuzzlePlatformerGameInstance::Host()
{

	UEngine* Engine = GetEngine();


	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting!"));
	

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");


}

void UPuzzlePlatformerGameInstance::Join(const FString& Address)
{

	UEngine* Engine = GetEngine();


	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, (TEXT("Joining Address : ") + Address));

	APlayerController* PC = GetFirstLocalPlayerController();

	if (!ensure(PC != nullptr)) return;

	PC->ClientTravel(Address, TRAVEL_Absolute);



}

void UPuzzlePlatformerGameInstance::BackToMenu()
{

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/MenuSystem/MainMenu_Level?listen");

}

void UPuzzlePlatformerGameInstance::LoadMenu()
{

	if (!ensure(MenuClass != nullptr)) return;

	MainMenu = CreateWidget<UMenuUserWidget>(this, MenuClass);

	if (!ensure(MainMenu != nullptr)) { return; }

	MainMenu->SetMenuInterface(this);

	MainMenu->Setup();


}

void UPuzzlePlatformerGameInstance::LoadGameMenu()
{

	if (!ensure(GameMenuClass != nullptr)) return;

	UGameMenuWidget* Menu = CreateWidget<UGameMenuWidget>(this, GameMenuClass, "Main Menu");

	if (!ensure(Menu != nullptr)) return;

	Menu->SetMenuInterface(this);

	Menu->Setup();


}
