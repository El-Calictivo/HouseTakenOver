// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipable.generated.h"


UINTERFACE(BlueprintType)
class UEquipable : public UInterface
{
	GENERATED_BODY()

};

class IEquipable
{
	GENERATED_BODY()

public:

	virtual void Equip() {}
	virtual void Unequip() {}
};
