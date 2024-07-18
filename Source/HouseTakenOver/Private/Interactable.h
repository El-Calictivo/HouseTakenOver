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


	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractableActor> InteractableOwner;

	UPROPERTY(VisibleAnywhere)
	class UPrimitiveComponent* InteractableTrigger;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* InteractableMesh;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUserInteractedEvent OnPlayerInteracted;

	UFUNCTION()
	void Initialize(TScriptInterface<IInteractableActor> OwnerActor, UPrimitiveComponent* TrigggerSet, UStaticMeshComponent* MeshSet);

	UFUNCTION()
	void Focus(bool bIsFocused);


	UFUNCTION()
	void Interact() const;

};
