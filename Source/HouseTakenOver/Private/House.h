// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Room.h>
#include "House.generated.h"

UCLASS()
class AHouse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHouse();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSet<ARoom*> Rooms;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<ARoom*> RoomsAvailable;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<ARoom*> RoomsTaken;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<ARoom*> RoomsBeingTaken;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<ARoom*> RoomsSealed;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ARoom* GetRandomRoom(ERoomState RoomState);

	UFUNCTION(BlueprintCallable)
	bool TryTakingRoom(ARoom* Room);

	void InitializeRoomCollections();

	void ClearRoomCollections();

	TArray<ARoom*>* GetRoomCollection(ERoomState RoomState);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnRoomStateChanged( ARoom* Room, const ERoomState OldState, const ERoomState NewState);

};
