// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserInteractedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserChangedFocus, bool, bIsFocused);


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

	UPROPERTY()
	class UPrimitiveComponent* Collider;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUserInteractedEvent OnPlayerInteracted;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUserChangedFocus OnPlayerChangedFocus;

	UFUNCTION()
	void Initialize(TScriptInterface<IInteractableActor> OwnerActor);

	UFUNCTION()
	void Focus(bool bIsFocused);

};
