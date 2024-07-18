// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include <FirstPersonCharacter.h>
#include <FirstPersonPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "InteractableActor.h"



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

}


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}





void UInteractable::Initialize(TScriptInterface<IInteractableActor> OwnerActor, UPrimitiveComponent* TrigggerSet, UStaticMeshComponent* MeshSet)
{
	InteractableTrigger = TrigggerSet;
	InteractableMesh = MeshSet;

	if (InteractableTrigger) {
		InteractableTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
		InteractableTrigger->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

	if (InteractableMesh) {
		InteractableMesh->SetCustomDepthStencilValue(1);
	}

	if (OwnerActor) {
		InteractableOwner = OwnerActor;
	}

}

void UInteractable::Focus(bool bIsFocused)
{
	if (!InteractableMesh)return;

	if (bIsFocused)InteractableMesh->SetRenderCustomDepth(true);
	else InteractableMesh->SetRenderCustomDepth(false);
}

void UInteractable::Interact() const
{

	OnPlayerInteracted.Broadcast();
}









