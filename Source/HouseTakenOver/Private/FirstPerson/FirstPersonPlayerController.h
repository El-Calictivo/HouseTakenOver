// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"


class UInteractable;
struct FInputActionValue;

UCLASS()
class AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UEnhancedInputComponent* EnhancedInputComponent;

	UPROPERTY()
	class AFirstPersonCharacter* FPCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Look(const FInputActionValue& Value);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	//Character Movement Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	class UInputAction* MoveCharacterAction;

	//Character Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	class UInputAction* MoveCameraAction;

	//Character Interaction Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	class UInputAction* InteractAction;



};
