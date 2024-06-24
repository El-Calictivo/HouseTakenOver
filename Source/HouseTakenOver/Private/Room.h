// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <RoomState.h>
#include "Room.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRoomStateChanged, ARoom*, Room, const ERoomState, OldState, const ERoomState, NewState);

UCLASS()
class ARoom : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoom();

protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float GraspedLevel;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSet<ARoom*> AdjacentRooms;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ERoomState RoomState = ERoomState::UNASSIGNED;
	
	UPROPERTY(EditInstanceOnly, meta = (ClampMin = 0, ClampMax = 1))
	float TakenInfluenceMultiplier = 1;

	UPROPERTY(EditInstanceOnly, meta = (ClampMin = 0, ClampMax = 1))
	float SealedInfluenceMultiplier = 0.25;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GraspRoom(float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void SetRoomState(ERoomState NewRoomState);

	UFUNCTION(BlueprintPure)
	ERoomState GetRoomState() const;

	UFUNCTION(BlueprintCallable)
	void InfluencAdjacentRooms(float GraspAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGraspedLevelChanged(float GraspLevel);

	UPROPERTY(BlueprintAssignable)
	FOnRoomStateChanged OnRoomStateChanged;

};
