// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include <FirstPerson/FirstPersonCharacter.h>
#include <FirstPerson/FirstPersonPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "InteractableActor.h"
#include "Components/WidgetComponent.h"


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





void UInteractable::Initialize(TScriptInterface<IInteractableActor> OwnerActor)
{

	if (!OwnerActor)return;

	InteractableOwner = OwnerActor;

	Collider = InteractableOwner->GetInteractableTrigger();
	Mesh = InteractableOwner->GetInteractableMesh();


	if (Collider) {
		Collider->SetCollisionResponseToAllChannels(ECR_Ignore);
		Collider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

	if (Mesh) {
		Mesh->SetCustomDepthStencilValue(1);
	}


}

void UInteractable::Focus(bool bIsFocused)
{
	OnPlayerChangedFocus.Broadcast(bIsFocused);

	if (Mesh)Mesh->SetRenderCustomDepth(bIsFocused);

}


