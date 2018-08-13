// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MenuSystem/MenuUserWidget.h"


void UServerRow::Setup(class UMenuUserWidget* Parent, uint32 Index)
{

	ServerButton->OnClicked.AddDynamic(this, &UServerRow::OnServerButtonClicked);

	MainMenu = Parent;
	RowIndex = Index;

}

void UServerRow::SetRowText(FString ServerName, FString UserName, FText PlayerCount)
{

	FText SText = FText::FromString(ServerName);
	FText NText = FText::FromString(UserName);

	this->ServerName->SetText(SText);
	this->UserName->SetText(NText);
	NumPlayers->SetText(PlayerCount);

}

void UServerRow::OnServerButtonClicked()
{

	MainMenu->SelectIndex(RowIndex);
	UE_LOG(LogTemp, Warning, TEXT("Selected Index : %i"), RowIndex);

}
