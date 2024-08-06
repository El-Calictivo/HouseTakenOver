// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TakenHouseGameMode.generated.h"

/**
 *
 */
UCLASS()
class ATakenHouseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATakenHouseGameMode();

protected:

	/*COOLDOWNS*/

	/** Cooldown Range in seconds until the house starts taking the first room */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown", meta = (ClampMin = "0.0"))
	FVector2f InitialGraspCooldown = FVector2f(30, 90);

	/** Cooldown Range in seconds for the rate the Rooms BeingTaken increase their Grasped Level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown", meta = (ClampMin = "0.0"))
	FVector2f GraspRoomCooldown = FVector2f(20, 40);

	/** Cooldown Range in seconds for the rate the Adjacent Rooms to Taken rooms increase their Grasped Level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown", meta = (ClampMin = "0.0"))
	FVector2f SpreadTakenRoomInfluenceCooldown = FVector2f(10, 30);

	/** Cooldown Range in seconds for the rate the Adjacent Rooms to Sealed rooms increase their Grasped Level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown", meta = (ClampMin = "0.0"))
	FVector2f SpreadSealedRoomInfluenceCooldown = FVector2f(10, 30);

	/*GRASP LEVELS*/

	/** Amount of Grasp Range to apply to Rooms being directly/actively taken */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grasp", meta = (ClampMin = "0.0"))
	FVector2f GraspForce = FVector2f(10, 15);

	/** Amount of Grasp Range to apply to Rooms adjacent to a Taken room */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grasp", meta = (ClampMin = "0.0"))
	FVector2f TakenRoomsInfluence = FVector2f(2, 7);

	/** Amount of Grasp Range to apply to Rooms adjacent to a Sealed room */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grasp", meta = (ClampMin = "0.0"))
	FVector2f SealedRoomsInfluence = FVector2f(2, 7);

	/** If TRUE, conditional statements will run to prevent a Room from start being taken if one is already in that process, if FALSE allows to multiple Room takings at a time */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bSingleGrasp = true;

protected:

	UFUNCTION(BlueprintCallable)
	class ARoom* TryGraspingAvailableRoom();

	UFUNCTION(BlueprintCallable)
	void IncreaseRoomsGrasp();

	UFUNCTION(BlueprintCallable)
	void SpreadTakenRoomsInfluence();

	UFUNCTION(BlueprintCallable)
	void SpreadSealedRoomsInfluence();

	UFUNCTION(BlueprintCallable)
	void IncreaseRoomsGraspBy(const ERoomState State, const float GraspAmount);

	UFUNCTION(BlueprintCallable)
	void IncreaseAdjacentRoomsGraspBy(const ERoomState State, const float GraspAmount);

};
