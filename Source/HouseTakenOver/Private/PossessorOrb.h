// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PossessorOrb.generated.h"

class ARoom;

UCLASS()
class APossessorOrb : public AActor
{
	GENERATED_BODY()

public:
	APossessorOrb();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bShouldAutoHideOnPlay;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InfluenceRoom(ARoom* RoomToAttach);
};
