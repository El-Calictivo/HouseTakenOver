// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ERoomState: uint8
{
	CLEAR UMETA(DisplayName = "Clear"),
	BEING_TAKEN UMETA(DisplayName = "Being Taken"),
	TAKEN UMETA(DisplayName = "Taken"),
	SEALED UMETA(DisplayName = "Sealed"),
};

