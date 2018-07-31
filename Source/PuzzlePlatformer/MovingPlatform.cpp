// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"




AMovingPlatform::AMovingPlatform()
{

	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	MoveSpeed = 20.0f;


}

void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();

	if (HasAuthority()) {

		SetReplicates(true);
		SetReplicateMovement(true);

	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{

	if (ActiveTriggers > 0) {

		ActiveTriggers--;
	}

}

void AMovingPlatform::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (ActiveTriggers > 0) {

		if (HasAuthority()) {



			FVector ActorLocation = GetActorLocation();

			float Length = (GlobalTargetLocation - GlobalStartLocation).Size();
			float Traveled = (ActorLocation - GlobalStartLocation).Size();

			if (Traveled > Length) {

				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;

			}

			FVector NewLocation = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

			ActorLocation += NewLocation * (MoveSpeed*DeltaSeconds);

			SetActorLocation(ActorLocation);

		}

	}

}
