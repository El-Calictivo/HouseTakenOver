// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <House/RoomState.h>
#include "HouseGraspSubsystem.generated.h"


class ARoom;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoomDelegate,  ARoom*, Room);

UCLASS()
class UHouseGraspSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:

	TArray<ARoom*> RoomsAvailable;
	TArray<ARoom*> RoomsTaken;
	TArray<ARoom*> RoomsBeingTaken;
	TArray<ARoom*> RoomsSealed;
	TArray<ARoom*> RoomsUnassigned;

	UFUNCTION()
	void OnRoomStateChanged(ARoom* Room, const ERoomState OldState, const ERoomState NewState);

public:
	TArray<ARoom*>* GetRoomCollection(const ERoomState RoomState);
	
	UFUNCTION()
	void RegisterRoom(ARoom* NewRoom);

	UFUNCTION(BlueprintPure)
	static float GetRandomValueFromRange(const FVector2f& ValueRange);

	UFUNCTION(BlueprintCallable)
	void GraspRoom(ARoom* Room, const float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void GraspRooms(const TArray<ARoom*> Rooms, const float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void GraspAdjacentRooms(const TArray<ARoom*> PivotRooms, const float GraspAmount);

	void GraspAdjacentRooms(const ARoom* PivotRoom, const float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void GraspRoomsByState(const ERoomState RoomsState, const float GraspAmount);

	UFUNCTION(BlueprintCallable)
	ARoom* GetRandomRoom(const ERoomState RoomState);

	FRoomDelegate OnRoomTaken;
};
