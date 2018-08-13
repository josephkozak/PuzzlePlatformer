// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public :

	void Setup(class UMenuUserWidget* Parent, uint32 Index);

	void SetRowText(FString ServerName, FString UserName, FText PlayerCount);
	
	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;

	
private :

	UMenuUserWidget * MainMenu;
	uint32 RowIndex;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UserName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NumPlayers;

	UPROPERTY(meta = (BindWidget))
	UButton* ServerButton;

	UFUNCTION()
	void OnServerButtonClicked();

};
