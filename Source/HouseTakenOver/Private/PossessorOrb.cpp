// Fill out your copyright notice in the Description page of Project Settings.

#include "PossessorOrb.h"
#include "House/Room.h"
#include "Subsystems/HouseGraspSubsystem.h"

// Sets default values
APossessorOrb::APossessorOrb()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APossessorOrb::BeginPlay()
{
	Super::BeginPlay();
	if (bShouldAutoHideOnPlay)
	{
		SetActorHiddenInGame(true);
	}

	GetWorld()->GetSubsystem<UHouseGraspSubsystem>()->RegisterPossessorOrb(this);
}

void APossessorOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APossessorOrb::InfluenceRoom(ARoom* RoomToAttach)
{
	if (RoomToAttach == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red,TEXT("Invalid room passed"));
		return false;
	}

	SetActorLocation(RoomToAttach->GetActorLocation());
	return true;
}
