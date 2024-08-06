// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdjacentRoom.generated.h"


USTRUCT(BlueprintType)
struct FAdjacentRoom
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, meta = (ClampMin = 0, ClampMax = 1))
	float ProximityInfluenceModifier = 1;

};