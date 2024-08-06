// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.h"
#include "Powerable.h"
#include "LightSwitch.generated.h"

UCLASS()
class ALightSwitch : public AActor, public IInteractableActor, public IPowerable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPrimitiveComponent* InteractionTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInteractable* InteractableComponent;


	UPROPERTY(EditInstanceOnly)
	TSet< AActor*> ConnectedLights;




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//IInteractableActor Functions
	virtual void InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor) override;
	virtual class UInteractable* GetInteractableComponent() const override { return InteractableComponent; }
	virtual class UStaticMeshComponent* GetInteractableMesh() const override { return Mesh; }
	virtual class UPrimitiveComponent* GetInteractableTrigger() const override { return InteractionTrigger; }

	//IPowerable Functions
	virtual void SetPowered(bool bIsOn) override;

	UFUNCTION()
	virtual void FlipFlopPower() override;


};
