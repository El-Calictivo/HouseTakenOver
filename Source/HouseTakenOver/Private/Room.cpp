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


void ARoom::SetVoidLevel(float NewVoidLevel)
{

	VoidLevel += NewVoidLevel;
	OnVoidLevelChanged(VoidLevel);

	if (VoidLevel >= 100) {
		VoidLevel = 100;
		SetRoomState(ERoomState::TAKEN);
	}
}

void ARoom::SetRoomState(ERoomState NewRoomState)
{
	ERoomState OldState = RoomState;
	RoomState = NewRoomState;
	OnRoomStateChanged.Broadcast(this, OldState, RoomState);
}//Closes SetRoomState Method

float ARoom::GetVoidLevel() const
{
	return VoidLevel;
}//Closes GetVoidLevel method

ERoomState ARoom::GetRoomState() const
{
	return RoomState;
}//Closes GetRoomState method

void ARoom::InfluencAdjacentRooms() {

	for (auto Room : AdjacentRooms) {
		if (Room == nullptr)continue;


	}
}





