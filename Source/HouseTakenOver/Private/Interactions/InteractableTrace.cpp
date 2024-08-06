// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTrace.h"
#include "Kismet/GameplayStatics.h"
#include "InteractableActor.h"
#include "Interactable.h"


// Sets default values for this component's properties
UInteractableTrace::UInteractableTrace()
{

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.25;

	CollisionQuery.AddIgnoredActor(GetOwner());

	// ...
}


void UInteractableTrace::SetFocusedInteractable(IInteractableActor* NewInteractable)
{
	if (FocusedInteractable) FocusedInteractable->GetInteractableComponent()->Focus(false);


	if (NewInteractable) {
		FocusedInteractable.SetInterface(NewInteractable);
		FocusedInteractable.SetObject(NewInteractable->_getUObject());
	}
	else FocusedInteractable = nullptr;

	if (FocusedInteractable)FocusedInteractable->GetInteractableComponent()->Focus(true);

}

// Called when the game starts
void UInteractableTrace::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

}

void UInteractableTrace::Trace()
{
	if (!CameraManager) return;

	FVector CameraPos = CameraManager->GetCameraLocation();
	FVector TraceEndPos = CameraPos + (CameraManager->GetActorForwardVector() * InteractionLength);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraPos, TraceEndPos, ECC_Visibility, CollisionQuery, CollisionResponse)) {

		AActor* HittedActor = HitResult.GetActor();


		if (FocusedInteractable.GetObject() == HittedActor) return;

		if (HittedActor->GetClass()->ImplementsInterface(UInteractableActor::StaticClass())) SetFocusedInteractable(Cast<IInteractableActor>(HittedActor));
		else SetFocusedInteractable(nullptr);

	}
	else SetFocusedInteractable(nullptr);
}




// Called every frame
void UInteractableTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Trace();

}

void UInteractableTrace::InteractFocuesedInteractable()
{
	if (!FocusedInteractable)return;
	FocusedInteractable->GetInteractableComponent()->OnPlayerInteracted.Broadcast();

}

