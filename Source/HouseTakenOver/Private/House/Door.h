// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/InteractableActor.h"
#include "Door.generated.h"


UENUM(BlueprintType)
enum class EDoorState : uint8 {
	OPEN UMETA(DisplayName = "Open"),
	CLOSED UMETA(DisplayName = "Closed"),
	SEALED UMETA(DisplayName = "Sealed"),
	TAKEN UMETA(DisplayName = "Taken"),

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorStateChanged, EDoorState, State);

UCLASS()
class ADoor : public AActor, public IInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator ClosedDoorAngle = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator OpenDoorAngle = FRotator(110, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Rotation")
	bool bInvertDirection = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPrimitiveComponent* InteractionTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInteractable* InteractableComponent;


	UFUNCTION()
	void FlipFlopDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;;

	UPROPERTY(EditAnywhere)
	EDoorState DoorState = EDoorState::CLOSED;

	UFUNCTION()
	void HandleOnDoorStateChanged(EDoorState NewDoorState);


public:


	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoorStateChanged OnDoorStateChanged;

	UFUNCTION()
	EDoorState GetState() const { return DoorState; }

	UFUNCTION()
	void SetDoorState(const EDoorState NewDoorState);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor) override;
	virtual class UInteractable* GetInteractableComponent() const override { return InteractableComponent; }
	virtual class UStaticMeshComponent* GetInteractableMesh() const override { return DoorMesh; }
	virtual class UPrimitiveComponent* GetInteractableTrigger() const override { return InteractionTrigger; }


};
