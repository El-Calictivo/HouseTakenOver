// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ARoom::GraspRoom(float GraspAmount)
{

	GraspedLevel += GraspAmount;

	if (GraspedLevel >= 100) {
		GraspedLevel = 100;
		if (RoomState != ERoomState::SEALED)SetRoomState(ERoomState::TAKEN);
	}

	OnGraspedLevelChanged(GraspedLevel);
}

void ARoom::SetRoomState(ERoomState NewRoomState)
{
	if (RoomState == NewRoomState)return;
	ERoomState OldState = RoomState;
	RoomState = NewRoomState;
	OnRoomStateChanged.Broadcast(this, OldState, RoomState);
}

ERoomState ARoom::GetRoomState() const
{
	return RoomState;
}

void ARoom::InfluencAdjacentRooms(float GraspAmount) {

	if (AdjacentRooms.IsEmpty())return;

	for (ARoom* Room : AdjacentRooms)
	{
		if (!Room)continue;

		if (RoomState == ERoomState::TAKEN)
			Room->GraspRoom(GraspAmount * TakenInfluenceMultiplier);
		else if (RoomState == ERoomState::SEALED)
			Room->GraspRoom(GraspAmount * SealedInfluenceMultiplier);
	}
}





