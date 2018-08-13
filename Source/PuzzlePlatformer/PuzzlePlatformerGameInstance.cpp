// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformerGameInstance.h"

#include "Engine/Engine.h"

//#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuUserWidget.h"
#include "MenuSystem/GameMenuWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/BaseMenuWidget.h"

#include "UnrealNames.h"

#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = NAME_GameSession;
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("HostingName");


UPuzzlePlatformerGameInstance::UPuzzlePlatformerGameInstance(const FObjectInitializer & ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<UUserWidget>  MenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	ConstructorHelpers::FClassFinder<UUserWidget>  GameMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));

	UE_LOG(LogTemp, Warning, TEXT("Constructed GameInstance"));

	if (!ensure(MenuWidgetClass.Class != nullptr)) return;
	if (!ensure(GameMenuWidgetClass.Class != nullptr)) return;

	MenuClass = MenuWidgetClass.Class;
	GameMenuClass = GameMenuWidgetClass.Class;

	CurrentServerName = FText::FromString("Unset");

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
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformerGameInstance::OnJoinSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformerGameInstance::OnFindSessionsComplete);
			
			FindServers();

		}



	}

}


void UPuzzlePlatformerGameInstance::Host(FText Name)
{

	CurrentServerName = Name;

	if (SessionInterface.IsValid()) {

		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExistingSession != nullptr) {

			UE_LOG(LogTemp, Warning, TEXT("Destroying Session"));
			SessionInterface->DestroySession(SESSION_NAME);

		}
		else {

			CreateSession(Name);
		}
	}
}

void UPuzzlePlatformerGameInstance::CreateSession(FText Name)
{

	if (SessionInterface.IsValid()) {

		FOnlineSessionSettings SessionSettings;

		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {

			SessionSettings.bIsLANMatch = true;

		}
		else {

			SessionSettings.bIsLANMatch = false;


		}

		SessionSettings.NumPublicConnections = 3;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bAllowJoinInProgress = false;
		FString ServerName = Name.ToString();
		SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

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

	World->ServerTravel("/Game/Maps/Lobby?listen");

	UE_LOG(LogTemp, Warning, TEXT("Created session %s"), *SessionName.ToString());	


}

void UPuzzlePlatformerGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{

	if (bSuccess) {

		CreateSession(CurrentServerName);
	}
}

void UPuzzlePlatformerGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Results)
{

	if (!SessionInterface.IsValid()) return;

	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	FString Address;

	if (!SessionInterface->GetResolvedConnectString(SessionName, Address)) {

		Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, (TEXT("Could not connect to host")));
		return;

	}

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, (TEXT("Joining Address : ") + Address));


	APlayerController* PC = GetFirstLocalPlayerController();

	if (!ensure(PC != nullptr)) return;

	PC->ClientTravel(Address, TRAVEL_Absolute);

}

void UPuzzlePlatformerGameInstance::OnFindSessionsComplete(bool bSuccess)
{

	//ServerNames.Empty();

	if (bSuccess && SessionSearch.IsValid() && MainMenu != nullptr) {


		UE_LOG(LogTemp, Warning, TEXT("Completed searching for sessions"));

		if (SessionSearch->SearchResults.Num() == 0) {

			UE_LOG(LogTemp, Warning, TEXT("Found 0 Sessions"));

		}
		else {

			TArray<FServerInfo> ServerList;

			for (int i = 0; i < SessionSearch->SearchResults.Num(); i++) {


				UE_LOG(LogTemp, Warning, TEXT("Found Session %i : %s"), i, *SessionSearch->SearchResults[i].GetSessionIdStr());

				FServerInfo Info;
				Info.ServerName = SessionSearch->SearchResults[i].GetSessionIdStr();

				Info.HostingPlayerName = SessionSearch->SearchResults[i].Session.OwningUserName;
				Info.MaxPlayers = SessionSearch->SearchResults[i].Session.SessionSettings.NumPublicConnections;
				Info.NumPlayers = (Info.MaxPlayers - SessionSearch->SearchResults[i].Session.NumOpenPublicConnections);

				FString Data;

				if (SessionSearch->SearchResults[i].Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, Data)) {

					UE_LOG(LogTemp, Warning, TEXT("Data %s was found!"), *Data);
					Info.ServerName = Data;

				}
				else {

				Info.ServerName = TEXT("Notset");

				}


				ServerList.Add(Info);


			}

			if (MainMenu->bIsEnabled) {

				MainMenu->SetServerList(ServerList);

			}
		}

	}

}

void UPuzzlePlatformerGameInstance::Join(uint32 Index)
{

	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	UEngine* Engine = GetEngine();

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

/*TArray<FServerInfo> UPuzzlePlatformerGameInstance::GetServerList()
{

	return ServerList;

}*/

void UPuzzlePlatformerGameInstance::FindServers()
{
	//ServerNames.Empty();

	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid()) {

		//SessionSearch->bIsLanQuery = true;

		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Started searching for sessions"));


	}

}

void UPuzzlePlatformerGameInstance::RefreshServerList()
{
	//ServerNames.Empty();
	//MainMenu->SetServerList(GetServerNames());
	FindServers();

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

		SessionInterface->EndSession(SESSION_NAME);


	}

}

void UPuzzlePlatformerGameInstance::StartGame()
{

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	if (SessionInterface.IsValid()) {

		SessionInterface->StartSession(SESSION_NAME);

	}
	World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");

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

	UGameMenuWidget* Menu = CreateWidget<UGameMenuWidget>(this, GameMenuClass, "Game Menu");

	if (!ensure(Menu != nullptr)) return;

	Menu->SetMenuInterface(this);

	Menu->Setup();


}
