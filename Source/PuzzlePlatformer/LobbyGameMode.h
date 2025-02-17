// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformerGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API ALobbyGameMode : public APuzzlePlatformerGameMode
{
	GENERATED_BODY()

public:

	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

	void StartGame();

	uint8 NumPlayers = 0;

	FTimerHandle StartTimer;
	
};
