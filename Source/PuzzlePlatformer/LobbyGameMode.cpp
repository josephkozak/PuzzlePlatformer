// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "PuzzlePlatformerGameInstance.h"


ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;

}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);

	NumPlayers++;

	if (NumPlayers >= 2) {

		UE_LOG(LogTemp, Warning, TEXT("Playercount is above 2; Starting game in 10 seconds..."));

		GetWorldTimerManager().SetTimer(StartTimer, this, &ALobbyGameMode::StartGame, 10.0f, false);
		if (GetWorldTimerManager().IsTimerActive(StartTimer)) {

			UE_LOG(LogTemp, Warning, TEXT("Timer is active"));

		}
	
	}

}

void ALobbyGameMode::Logout(AController* Exiting)
{

	Super::Logout(Exiting);


	UE_LOG(LogTemp, Warning, TEXT("%s has left the game!"), *Exiting->GetFullName());

	NumPlayers--;

}

void ALobbyGameMode::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Finished Timer"));


	UPuzzlePlatformerGameInstance* GameInstance = Cast<UPuzzlePlatformerGameInstance>(GetGameInstance());

	if (GameInstance) {

		GameInstance->StartGame();

	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("GameInstance is NULL"));

	}

}
