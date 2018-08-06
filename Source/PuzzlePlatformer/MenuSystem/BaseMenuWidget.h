// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	bool Initialize();
	IMenuInterface* MenuInterface;

public:

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

	virtual void DestroyMenu();

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:



	
	
};
