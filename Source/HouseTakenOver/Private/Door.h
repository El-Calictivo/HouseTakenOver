// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.h"
#include "Door.generated.h"


UCLASS()
class ADoor : public AActor, public IInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

private:

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly)
	class UPrimitiveComponent* InteractionTrigger;

	UPROPERTY(EditDefaultsOnly)
	class UInteractable* InteractableComponent;

	UFUNCTION()
	void FlipFlopDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;;

	UPROPERTY(EditAnywhere)
	bool bIsOpen;

	UPROPERTY(EditAnywhere)
	bool bIsSealed;


public:

	UFUNCTION()
	bool SetIsOpen(bool isOpen);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor, UPrimitiveComponent* TrigggerSet, UStaticMeshComponent* MeshSet) override;
	virtual class UInteractable* GetInteractableComponent() override;

};
