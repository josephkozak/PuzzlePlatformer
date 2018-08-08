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
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("Session Test");

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

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem == nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("Subsystem is NULLPTR"));

	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("Subsystem is not NULLPTR; name is %s"), *Subsystem->GetSubsystemName().ToString());

		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformerGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformerGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformerGameInstance::OnFindSessionsComplete);

			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			if (SessionSearch.IsValid()) {

				SessionSearch->bIsLanQuery = true;

				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
				UE_LOG(LogTemp, Warning, TEXT("Started searching for sessions"));


			}
		}

	}

}


void UPuzzlePlatformerGameInstance::Host()
{


	if (SessionInterface.IsValid()) {

		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExistingSession != nullptr) {

			UE_LOG(LogTemp, Warning, TEXT("Destroying Session"));
			SessionInterface->DestroySession(SESSION_NAME);

		} else {

			CreateSession();
		}
	}
}

void UPuzzlePlatformerGameInstance::CreateSession()
{

	if (SessionInterface.IsValid()) {

		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);

	}
}

void UPuzzlePlatformerGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess) {

	if (!bSuccess) {

		UE_LOG(LogTemp, Warning, TEXT("Could not create session %s"), *SessionName.ToString());
		return;

	}

	UEngine* Engine = GetEngine();


	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting!"));


	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");

	UE_LOG(LogTemp, Warning, TEXT("Created session %s"), *SessionName.ToString());
	


}

void UPuzzlePlatformerGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{

	if (bSuccess) {

		CreateSession();
	}
}

void UPuzzlePlatformerGameInstance::OnFindSessionsComplete(bool bSuccess)
{

	if (bSuccess) {


		UE_LOG(LogTemp, Warning, TEXT("Completed searching for sessions"));

		for (int i = 0; i < SessionSearch->SearchResults.Num(); i++) {


			UE_LOG(LogTemp, Warning, TEXT("Found Session %i : %s"), i, *SessionSearch->SearchResults[i].GetSessionIdStr());

		}


	}

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

	APlayerController* PC = GetFirstLocalPlayerController();

	if (!ensure(PC != nullptr)) return;

	if (PC->Role != ROLE_Authority) {

		PC->ClientTravel("/Game/MenuSystem/MainMenu_Level", TRAVEL_Absolute);

	}
	else {

		for (FConstPlayerControllerIterator PCIterator = GetWorld()->GetPlayerControllerIterator(); PCIterator; ++PCIterator) {


			APlayerController* PC2 = PCIterator->Get();

			if (!ensure(PC2 != nullptr)) return;

			PC2->ClientTravel("/Game/MenuSystem/MainMenu_Level", TRAVEL_Absolute);

		}

	}

}

void UPuzzlePlatformerGameInstance::LoadMenuWidget()
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
