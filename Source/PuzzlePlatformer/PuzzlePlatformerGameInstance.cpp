// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformerGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

#include "PlatformTrigger.h"

UPuzzlePlatformerGameInstance::UPuzzlePlatformerGameInstance(const FObjectInitializer & ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<APlatformTrigger>  PlatformPawnClass(TEXT("/Game/BPS/PlatformTrigger_BP"));

	UE_LOG(LogTemp, Warning, TEXT("Constructed GameInstance"));

	if (!ensure(PlatformPawnClass.Class != nullptr)) return;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformPawnClass.Class->GetName());

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

	World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");



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