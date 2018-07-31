// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformerGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


UPuzzlePlatformerGameInstance::UPuzzlePlatformerGameInstance(const FObjectInitializer & ObjectInitializer)
{

	UE_LOG(LogTemp, Warning, TEXT("Constructed GameInstance"));

}

void UPuzzlePlatformerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance INIT"));

}

void UPuzzlePlatformerGameInstance::Host()
{

	UEngine* Engine = GetEngine();


	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting!"));
	

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");



}

void UPuzzlePlatformerGameInstance::Join(const FString& Address)
{

	UEngine* Engine = GetEngine();


	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, (TEXT("Joining Address : ") + Address));

	APlayerController* PC = GetFirstLocalPlayerController();

	if (!ensure(PC != nullptr)) return;

	PC->ClientTravel(Address, TRAVEL_Absolute);



}