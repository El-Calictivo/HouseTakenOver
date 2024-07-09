// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserInteractedEvent);
class AFirstPersonPlayerController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UInteractable : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AFirstPersonPlayerController* PlayerController;

	UPROPERTY()
	uint32 InteractionHandle=0;

	UPROPERTY(VisibleAnywhere)
	class UPrimitiveComponent* Collider;

	UFUNCTION()
	void OnInteractableOnRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractableOutsideRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUserInteractedEvent OnPlayerInteracted;

	UFUNCTION()
	void SetCollider(UPrimitiveComponent* NewCollider);

	UFUNCTION()
	void Interact();

};
