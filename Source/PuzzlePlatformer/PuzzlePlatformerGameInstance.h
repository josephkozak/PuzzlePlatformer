// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformerGameInstance.generated.h"




class UUserWidget;
class UMenuUserWidget;
class FOnlineSessionSearch;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPuzzlePlatformerGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPuzzlePlatformerGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(exec)
	virtual void Host(FText Name) override;

	UFUNCTION(exec)
	virtual void Join(uint32 Index) override;

	//virtual TArray<FServerInfo> GetServerList() override;
	
	virtual void FindServers() override;

	virtual void RefreshServerList() override;

	virtual void BackToMenu() override;

	void StartGame();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadGameMenu();

	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> GameMenuClass;

private:

	UMenuUserWidget * MainMenu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	void CreateSession(FText Name);

	FText CurrentServerName;

	UFUNCTION()
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	
	UFUNCTION()
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Results);

	UFUNCTION()
	void OnFindSessionsComplete( bool bSuccess);

};
