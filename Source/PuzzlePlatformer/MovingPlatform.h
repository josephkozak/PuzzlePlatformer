// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();

	virtual void BeginPlay() override;

	//Movement in centimeters per second

	UPROPERTY(EditAnywhere, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Destination", Meta = (MakeEditWidget=true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	int32 ActiveTriggers = 1;
	
protected:

	virtual void Tick(float DeltaSeconds) override;
	
};
