// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactions/InteractableActor.h"
#include "Window.generated.h"

class ARoom;

UENUM(BlueprintType)
enum class EWindowState : uint8 {
	OPEN UMETA(DisplayName = "Open"),
	CLOSED UMETA(DisplayName = "Closed"),
	TAKEN UMETA(DisplayName = "Taken"),
};

UCLASS()
class AWindow : public AActor, public IInteractableActor
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInteractable* InteractableComponent;

public:
	// Sets default values for this actor's properties
	AWindow();

	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly);
	ARoom* Room;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	FVector2f GraspRoomCooldown = FVector2f(20, 40);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	FVector2f GraspForce = FVector2f(2, 5);


	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	EWindowState WindowState = EWindowState::CLOSED;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ReopeningChance = 0.15f;

	UFUNCTION(BlueprintCallable)
	void IncreaseRoomGrasp(float GraspAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWindowStateChanged(const EWindowState OldState, const EWindowState NewState);

	UFUNCTION()
	void OnRoomGraspLevelChanged(ARoom* ChangedRoom, float OldGraspLevel, float NewGraspLevel);

	UFUNCTION()
	bool TryOpeningWindow() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetState(EWindowState NewState);


public:
	//Interactable Actor Interface method
	virtual void InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor) override;
	virtual class UInteractable* GetInteractableComponent() const override { return nullptr; }
	virtual class UStaticMeshComponent* GetInteractableMesh() const override { return nullptr; }
	virtual class UPrimitiveComponent* GetInteractableTrigger() const override { return nullptr; }

};
