// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/BaseMenuWidget.h"
#include "MenuUserWidget.generated.h"


class UButton;
class UEditableTextBox;
class UPuzzlePlatformerGameInstance;
class UWidgetSwitcher;
class UScrollBox;

USTRUCT()
struct FServerInfo {

	GENERATED_BODY()


	FString ServerName;
	
	FString HostingPlayerName;

	uint8 NumPlayers;
	uint8 MaxPlayers;


};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMenuUserWidget : public UBaseMenuWidget
{
	GENERATED_BODY()


public:

	UMenuUserWidget(const FObjectInitializer & ObjectInitializer);

	TSubclassOf<UUserWidget> TextBlockClass;

	void SetServerList(TArray<FServerInfo> Servers);

	void SelectIndex(uint32 Index);

protected:

	bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HostBack;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServer;

	UPROPERTY(meta = (BindWidget))
	UButton* CreateGame;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ServerName;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ServerAddresses;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UFUNCTION()
	void OnHostButtonClicked();

	UFUNCTION()
	void OnCreateGameButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnRefreshButtonClicked();

	UFUNCTION()
	void OnJoinServerButtonClicked();

	void UpdateChildren();

	TOptional<uint32> SelectedIndex;
	
	
};
