// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerable.generated.h"


UINTERFACE(BlueprintType)
class UPowerable : public UInterface
{
	GENERATED_BODY()

};

class IPowerable
{
	GENERATED_BODY()

public:

	virtual void SetPowered(bool bIsOn) {}
	virtual void FlipFlopPower() {}
	virtual bool IsPowered() const { return false; }

};
