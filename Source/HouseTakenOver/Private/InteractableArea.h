// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableArea.generated.h"

UCLASS()
class AInteractableArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* Trigger;

	UPROPERTY()
	bool bIsFocused;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetIsFocused(bool bSetIsFocused);

};
