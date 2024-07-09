// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include <FirstPersonCharacter.h>
#include <FirstPersonPlayerController.h>
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AFirstPersonPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

}


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractable::SetCollider(UPrimitiveComponent* NewCollider)
{
	if (Collider) {

		Collider->OnComponentBeginOverlap.RemoveDynamic(this, &UInteractable::OnInteractableOnRange);
		Collider->OnComponentEndOverlap.RemoveDynamic(this, &UInteractable::OnInteractableOutsideRange);

	}

	if (NewCollider) {

		NewCollider->OnComponentBeginOverlap.AddDynamic(this, &UInteractable::OnInteractableOnRange);
		NewCollider->OnComponentEndOverlap.AddDynamic(this, &UInteractable::OnInteractableOutsideRange);
	}

	Collider = NewCollider;
}

void UInteractable::Interact()
{
	OnPlayerInteracted.Broadcast();
}



void UInteractable::OnInteractableOnRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!PlayerController)return;
	InteractionHandle = PlayerController->BindInteractable(this);

}

void UInteractable::OnInteractableOutsideRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!PlayerController)return;
	PlayerController->RemoveInteractable(InteractionHandle);


}






