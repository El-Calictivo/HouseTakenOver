// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomState.h"
#include <House/AdjacentRoom.h>
#include "Room.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRoomStateChanged, ARoom*, Room, const ERoomState, OldState, const ERoomState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGraspLevelChanged, ARoom*, Room, const float, OldLevel, const float, NewLevel);

UCLASS()
class ARoom : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoom();

protected:


	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPrimitiveComponent* RoomBounds;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Grasp")
	ERoomState RoomState = ERoomState::UNASSIGNED;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grasp")
	float GraspedLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grasp")
	float GraspLevelLimit = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grasp")
	UCurveFloat* DesaturationPostVfxCurve;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "House")
	TMap<ARoom*, FAdjacentRoom> AdjacentRooms;

	UPROPERTY(EditInstanceOnly, Category = "House")
	TSet<class ADoor*> ConnectedDoors;



	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Debug")
	bool bDegugLines = true;

	UFUNCTION()
	void OnGraspedLevelChanged(float GraspLevel);


	UFUNCTION()
	bool IsLocked();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	float GetNormalizedGraspLevel() const { return GraspedLevel / GraspLevelLimit; };

	UFUNCTION(BlueprintCallable)
	void IncreaseGraspLevel(float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void SetRoomState(ERoomState NewRoomState);

	UFUNCTION(BlueprintPure)
	ERoomState GetRoomState() const;


	UPROPERTY(BlueprintAssignable)
	FOnRoomStateChanged OnRoomStateChanged;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnGraspLevelChanged OnGraspLevelChanged;

	UFUNCTION()
	void OnDoorStateChanged(enum EDoorState NewDoorState);

	TMap<ARoom*, FAdjacentRoom> GetAdjacentRooms() const { return AdjacentRooms; };

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void DrawAdjacentRoomsConnectionNodes(const float Lifetime = 0.1);
	void DrawConnectedDoorNodes(const float Lifetime = 0.1);

#endif

};
