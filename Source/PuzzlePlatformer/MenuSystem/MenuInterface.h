// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMER_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//TArray<FServerInfo> ServerInfo;

	//virtual TArray<FServerInfo> GetServerInfo() = 0;

	virtual void Host(FText Name) = 0;
	virtual void Join(uint32 Index) = 0;

	virtual void BackToMenu() = 0;

	virtual void FindServers() = 0;

	virtual void RefreshServerList() = 0;

};
