// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionQueryParams.h"
#include "InteractableTrace.generated.h"

class IInteractableActor;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UInteractableTrace : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableTrace();

private:
	FCollisionQueryParams CollisionQuery;
	FCollisionResponseParams CollisionResponse;
	FHitResult HitResult;
	void SetFocusedInteractable(IInteractableActor* NewInteractable);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float InteractionLength = 300;

	UFUNCTION()
	void Trace();

	UPROPERTY()
	class APlayerCameraManager* CameraManager;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractableActor> FocusedInteractable;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InteractFocuesedInteractable();

};
