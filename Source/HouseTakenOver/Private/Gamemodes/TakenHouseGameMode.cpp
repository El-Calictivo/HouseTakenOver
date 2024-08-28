// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/TakenHouseGameMode.h"
#include "House/Room.h"
#include "Kismet/KismetMathLibrary.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "Subsystems/HouseGraspSubsystem.h"
#include "FirstPerson/FirstPersonPlayerController.h"


ATakenHouseGameMode::ATakenHouseGameMode()
{

	DefaultPawnClass = AFirstPersonCharacter::StaticClass();
	PlayerControllerClass = AFirstPersonPlayerController::StaticClass();

}



ARoom* ATakenHouseGameMode::TryGraspingAvailableRoom()
{
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return nullptr;


	TArray<ARoom*>* RoomsAvailable = HouseGraspSubsystem->GetRoomCollection(ERoomState::AVAILABLE);
	if (RoomsAvailable->IsEmpty())return nullptr;

	if (bSingleGrasp) {
		TArray<ARoom*>* RoomsBeingTaken = HouseGraspSubsystem->GetRoomCollection(ERoomState::BEING_TAKEN);
		if (!RoomsBeingTaken->IsEmpty())return nullptr;
	}

	ARoom* AvailableRoom = HouseGraspSubsystem->GetRandomRoom(ERoomState::AVAILABLE);

	if (AvailableRoom) {

		AvailableRoom->SetRoomState(ERoomState::BEING_TAKEN);
		AvailableRoom->OnRoomStateChanged.AddUniqueDynamic(this, &ATakenHouseGameMode::OnRoomStateChanged);
	}

	return AvailableRoom;

}

void ATakenHouseGameMode::OnRoomStateChanged(ARoom* Room, const ERoomState OldState, ERoomState NewState)
{
	if (!Room)return;
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return;


	if (NewState == ERoomState::TAKEN) {

		Room->OnRoomStateChanged.RemoveDynamic(this, &ATakenHouseGameMode::OnRoomStateChanged);
		OnRoomTaken(Room);
		if (HouseGraspSubsystem->GetRoomCollection(ERoomState::BEING_TAKEN)->IsEmpty())OnLastRoomTaken(Room);
	}

}



void ATakenHouseGameMode::IncreaseRoomsGrasp()
{
	IncreaseRoomsGraspBy(ERoomState::BEING_TAKEN, UHouseGraspSubsystem::GetRandomValueFromRange(GraspForce));

}

void ATakenHouseGameMode::SpreadTakenRoomsInfluence()
{
	IncreaseAdjacentRoomsGraspBy(ERoomState::TAKEN, UHouseGraspSubsystem::GetRandomValueFromRange(TakenRoomsInfluence));
}

void ATakenHouseGameMode::SpreadSealedRoomsInfluence()
{
	IncreaseAdjacentRoomsGraspBy(ERoomState::SEALED, UHouseGraspSubsystem::GetRandomValueFromRange(SealedRoomsInfluence));
}

void ATakenHouseGameMode::InitializeGraspSubsystem()
{
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return;

	HouseGraspSubsystem->SetGraspProgression(GraspForceProgressionCurve);
	HouseGraspSubsystem->SetHoursTillDawn(NightDuration);

}

void ATakenHouseGameMode::NextHour()
{
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return;
	HouseGraspSubsystem->AdvanceDay();
}


void ATakenHouseGameMode::IncreaseRoomsGraspBy(const ERoomState State, const float GraspAmount)
{
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return;

	HouseGraspSubsystem->GraspRoomsByState(State, GraspAmount * HouseGraspSubsystem->GetCurrentGraspForceMultiplier());

}

void ATakenHouseGameMode::IncreaseAdjacentRoomsGraspBy(const ERoomState State, const float GraspAmount)
{
	UHouseGraspSubsystem* HouseGraspSubsystem = GetWorld()->GetSubsystem<UHouseGraspSubsystem>();
	if (!HouseGraspSubsystem)return;

	HouseGraspSubsystem->GraspAdjacentRooms(*HouseGraspSubsystem->GetRoomCollection(ERoomState::TAKEN), GraspAmount * HouseGraspSubsystem->GetCurrentGraspForceMultiplier());
}



