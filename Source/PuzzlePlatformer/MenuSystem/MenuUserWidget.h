// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/BaseMenuWidget.h"
#include "MenuUserWidget.generated.h"


class UButton;
class UEditableTextBox;
class UPuzzlePlatformerGameInstance;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMenuUserWidget : public UBaseMenuWidget
{
	GENERATED_BODY()


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
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServer;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAddress;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UFUNCTION()
	void OnHostButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnJoinServerButtonClicked();
	
	
};
