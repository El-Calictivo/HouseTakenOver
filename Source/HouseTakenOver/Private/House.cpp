// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"

// Sets default values
AHouse::AHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{

	InitializeRoomCollections();
	Super::BeginPlay();

}

ARoom* AHouse::GetRandomRoom(ERoomState RoomState)
{
	TArray<ARoom*>* RoomCollection = GetRoomCollection(RoomState);

	if (RoomCollection == nullptr || RoomCollection->IsEmpty()) return nullptr;


	int8 RandomIndex = FMath::RandRange(0, RoomCollection->Num() - 1);

	ARoom* RandomRoom = (*RoomCollection)[RandomIndex];

	if (RandomRoom != nullptr) return RandomRoom;

	RoomCollection->RemoveAt(RandomIndex);
	return GetRandomRoom(RoomState);
}

bool AHouse::TryTakingRoom(ARoom* Room)
{

	if (Room == nullptr || Room->GetRoomState() != ERoomState::CLEAR)return false;
	Room->SetRoomState(ERoomState::BEING_TAKEN);

	return true;
}

void AHouse::InitializeRoomCollections()
{

	ClearRoomCollections();

	for (ARoom* Room : Rooms)
	{
		if (Room == nullptr)continue;

		Room->OnRoomStateChanged.AddDynamic(this, &AHouse::OnRoomStateChanged);
		GetRoomCollection(Room->GetRoomState())->AddUnique(Room);
		Room->SetRoomState(Room->GetRoomState());
	}
}


void AHouse::ClearRoomCollections()
{
	RoomsAvailable.Empty();
	RoomsBeingTaken.Empty();
	RoomsTaken.Empty();
	RoomsSealed.Empty();
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

	case ERoomState::CLEAR:
	default:
		return  &RoomsAvailable;
	}
}

void AHouse::OnRoomStateChanged_Implementation(ARoom* Room, const ERoomState OldState, const ERoomState NewState)
{
	if (Room == nullptr)return;

	GetRoomCollection(OldState)->Remove(Room);
	GetRoomCollection(NewState)->AddUnique(Room);
	UE_LOG(LogTemp, Warning, TEXT("USED FROM C++"));
}



void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}//Closes Tick method

