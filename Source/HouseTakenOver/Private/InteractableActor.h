// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.generated.h"


UINTERFACE(BlueprintType)
class UInteractableActor : public UInterface
{
	GENERATED_BODY()

};

class IInteractableActor
{
	GENERATED_BODY()

public:

	virtual void InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor, UPrimitiveComponent* TrigggerSet, UStaticMeshComponent* MeshSet) {}
	virtual class UInteractable* GetInteractableComponent() { return nullptr; }

};
