// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonCharacter.h"
#include "Interactable.h"


void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {

		Subsystem->AddMappingContext(DefaultMappingContext, 0);

	}

	FPCharacter = Cast<AFirstPersonCharacter>(GetPawn());

}

void AFirstPersonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(MoveCharacterAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::Move);
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::Interact);
	}
}

void AFirstPersonPlayerController::Move(const FInputActionValue& Value)
{

	FVector2D InputVector = Value.Get<FVector2D>();

	FPCharacter->AddMovementInput(GetPawn()->GetActorRightVector(), InputVector.X);
	FPCharacter->AddMovementInput(GetPawn()->GetActorForwardVector(), InputVector.Y);

}

void AFirstPersonPlayerController::Interact()
{
	FPCharacter->Interact();
}

void AFirstPersonPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	FPCharacter->AddControllerYawInput(InputVector.X);
	FPCharacter->AddControllerPitchInput(InputVector.Y);
}





