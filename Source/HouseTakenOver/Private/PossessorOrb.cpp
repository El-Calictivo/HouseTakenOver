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

void APossessorOrb::InfluenceRoom(ARoom* RoomToAttach)
{
	SetActorLocation(RoomToAttach->GetActorLocation());
}
