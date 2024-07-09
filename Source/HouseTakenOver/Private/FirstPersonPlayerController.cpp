// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactable.h"


void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {

		Subsystem->AddMappingContext(DefaultMappingContext, 0);

	}
}

void AFirstPersonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(MoveCharacterAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::Move);
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::Look);

	}
}

void AFirstPersonPlayerController::Move(const FInputActionValue& Value)
{

	FVector2D InputVector = Value.Get<FVector2D>();

	GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), InputVector.X);
	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), InputVector.Y);

}

void AFirstPersonPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	GetPawn()->AddControllerYawInput(InputVector.X);
	GetPawn()->AddControllerPitchInput(InputVector.Y);
}

uint32 AFirstPersonPlayerController::BindInteractable(UInteractable* Interactable)
{
	if (!Interactable || !EnhancedInputComponent)return 0;

	FEnhancedInputActionEventBinding& Interaction = EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, Interactable, &UInteractable::Interact);
	return Interaction.GetHandle();

}

void AFirstPersonPlayerController::RemoveInteractable(uint32& Binding)
{
	if (!EnhancedInputComponent)return;
	EnhancedInputComponent->RemoveBindingByHandle(Binding);
	
}



