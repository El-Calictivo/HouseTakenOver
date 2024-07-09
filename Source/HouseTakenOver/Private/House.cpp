// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"
#include "Room.h"

// Sets default values
AHouse::AHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{

	ClearRoomCollections();

	for (ARoom* Room : Rooms)
	{
		if (!Room)continue;

		Room->OnRoomStateChanged.AddDynamic(this, &AHouse::OnRoomStateChanged);
		Room->SetRoomState(ERoomState::AVAILABLE);
	}
	Super::BeginPlay();

}

ARoom* AHouse::GetRandomRoom(ERoomState RoomState)
{
	TArray<ARoom*>* RoomCollection = GetRoomCollection(RoomState);

	if (!RoomCollection || RoomCollection->IsEmpty()) return nullptr;


	int8 RandomIndex = FMath::RandRange(0, RoomCollection->Num() - 1);

	ARoom* RandomRoom = (*RoomCollection)[RandomIndex];

	if (RandomRoom!=nullptr) return RandomRoom;

	RoomCollection->RemoveAt(RandomIndex);
	return GetRandomRoom(RoomState);
}

void AHouse::ClearRoomCollections()
{
	RoomsAvailable.Empty();
	RoomsBeingTaken.Empty();
	RoomsTaken.Empty();
	RoomsSealed.Empty();
	RoomsUnassigned.Empty();
}

TArray<ARoom*>* AHouse::GetRoomCollection(ERoomState RoomState)
{

	switch (RoomState)
	{

	case ERoomState::BEING_TAKEN:
		return  &RoomsBeingTaken;

	case ERoomState::TAKEN:
		return  &RoomsTaken;

	case ERoomState::SEALED:
		return  &RoomsSealed;

	case ERoomState::AVAILABLE:
		return  &RoomsAvailable;

	case ERoomState::UNASSIGNED:
	default:
		return  &RoomsUnassigned;
	}
}

void AHouse::OnRoomStateChanged_Implementation(ARoom* Room, const ERoomState OldState, const ERoomState NewState)
{
	

	GetRoomCollection(OldState)->Remove(Room);
	GetRoomCollection(NewState)->AddUnique(Room);

	//switch (NewState)
	//{
	//default:
	//	break;
	//}
}

void AHouse::IncreaseHouseGrasp(float GraspAmount)
{
	if (RoomsBeingTaken.IsEmpty())return;

	for (ARoom* Room : RoomsBeingTaken)
	{
		if (!Room)continue;
		Room->GraspRoom(GraspAmount);
	}

}
ARoom* AHouse::TakeNewRoom()
{
	if (RoomsAvailable.IsEmpty() || !RoomsBeingTaken.IsEmpty())return nullptr;

	ARoom* ValidRoom = GetRandomRoom(ERoomState::AVAILABLE);

	if (!ValidRoom) return nullptr;

	ValidRoom->SetRoomState(ERoomState::BEING_TAKEN);

	return ValidRoom;

}




void AHouse::RadiateGraspInfluence(float GraspAmount)
{
	if (RoomsSealed.IsEmpty() && RoomsTaken.IsEmpty())return;

	TArray<ARoom*> InfluencerRooms;

	InfluencerRooms.Append(*GetRoomCollection(ERoomState::TAKEN));
	InfluencerRooms.Append(*GetRoomCollection(ERoomState::SEALED));


	for (ARoom* Room : InfluencerRooms)
	{
		if (!Room)continue;
		Room->InfluencAdjacentRooms(GraspAmount);
	}

}//Closes IncreaseHouseGrasp method

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}//Closes Tick method

