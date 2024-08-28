// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/HouseGraspSubsystem.h"
#include "House/Room.h"

void UHouseGraspSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}


void UHouseGraspSubsystem::RegisterRoom(ARoom* NewRoom)
{
	if (!NewRoom)return;
	NewRoom->OnRoomStateChanged.AddUniqueDynamic(this, &UHouseGraspSubsystem::OnRoomStateChanged);
	NewRoom->OnRoomStateChanged.Broadcast(NewRoom, ERoomState::UNASSIGNED, NewRoom->GetRoomState());

}

void UHouseGraspSubsystem::GraspRoom(ARoom* Room, const float GraspAmount)
{
	if (Room) Room->IncreaseGraspLevel(GraspAmount);
}

void UHouseGraspSubsystem::GraspRooms(const TArray<ARoom*> Rooms, const float GraspAmount)
{
	for (ARoom* Room : Rooms) GraspRoom(Room, GraspAmount);
}

void UHouseGraspSubsystem::GraspRoomsByState(const ERoomState RoomsState, const float GraspAmount)
{
	GraspRooms(*GetRoomCollection(RoomsState), GraspAmount);
}

void UHouseGraspSubsystem::GraspAdjacentRooms(const TArray<ARoom*> PivotRooms, const float GraspAmount)
{
	for (auto PivotRoom : PivotRooms) GraspAdjacentRooms(PivotRoom, GraspAmount);

}

void UHouseGraspSubsystem::GraspAdjacentRooms(const ARoom* PivotRoom, const float GraspAmount)
{
	if (!PivotRoom)return;

	for (auto& AdjacentRoomPair : PivotRoom->GetAdjacentRooms())
	{
		if (!AdjacentRoomPair.Key)continue;
		GraspRoom(AdjacentRoomPair.Key, GraspAmount * AdjacentRoomPair.Value.ProximityInfluenceModifier);

	}
}

ARoom* UHouseGraspSubsystem::GetRandomRoom(const ERoomState RoomState)
{
	TArray<ARoom*>* RoomCollection = GetRoomCollection(RoomState);

	if (!RoomCollection || RoomCollection->IsEmpty()) return nullptr;

	int8 RandomIndex = FMath::RandRange(0, RoomCollection->Num() - 1);
	ARoom* RandomRoom = (*RoomCollection)[RandomIndex];


	if (RandomRoom) {
		return RandomRoom;
	}
	else {
		RoomCollection->RemoveAt(RandomIndex);
		return GetRandomRoom(RoomState);
	}
}

void UHouseGraspSubsystem::AdvanceDay()
{
	Hours++;
	if (Hours >= HoursTillDawn) {
		Hours = HoursTillDawn;

	}
}

float UHouseGraspSubsystem::GetProgress() const
{
	return Hours / HoursTillDawn;
}

float UHouseGraspSubsystem::GetCurrentGraspForceMultiplier() const
{
	if (!GraspProgression)return 1;
	return GraspProgression->GetFloatValue(GetProgress());

}

float UHouseGraspSubsystem::GetRandomValueFromRange(const FVector2f& ValueRange)
{
	return FMath::RandRange(FMath::Min(ValueRange.X, ValueRange.Y), FMath::Max(ValueRange.X, ValueRange.Y));

}

TArray<ARoom*>* UHouseGraspSubsystem::GetRoomCollection(const ERoomState RoomState)
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

void UHouseGraspSubsystem::SetHoursTillDawn(uint8 NewHoursTillDawn)
{
	HoursTillDawn = NewHoursTillDawn;
}

void UHouseGraspSubsystem::SetGraspProgression(UCurveFloat* NewGraspProgression)
{
	GraspProgression = NewGraspProgression;
}


void UHouseGraspSubsystem::OnRoomStateChanged(ARoom* Room, const ERoomState OldState, const ERoomState NewState)
{
	GetRoomCollection(OldState)->Remove(Room);
	GetRoomCollection(NewState)->AddUnique(Room);

	if (NewState == ERoomState::TAKEN) OnRoomTaken.Broadcast(Room);
}

void UHouseGraspSubsystem::Deinitialize()
{
	UEnum* ERoomStatePtr = StaticEnum<ERoomState>();

	for (uint8 i = 0; i < ERoomStatePtr->NumEnums() - 1; ++i)
	{
		TArray<ARoom*>* RoomCollection = GetRoomCollection(StaticCast<ERoomState>(i));

		if (RoomCollection) {

			for (auto Room : *RoomCollection) {
				if (Room)Room->OnRoomStateChanged.RemoveDynamic(this, &UHouseGraspSubsystem::OnRoomStateChanged);

			}

			RoomCollection->Empty();
		}
	}

}
