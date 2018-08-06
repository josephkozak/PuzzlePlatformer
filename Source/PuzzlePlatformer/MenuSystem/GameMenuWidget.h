// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/BaseMenuWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "GameMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UGameMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()


protected:

	bool Initialize();

private:
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnCancelButtonClicked();

};
