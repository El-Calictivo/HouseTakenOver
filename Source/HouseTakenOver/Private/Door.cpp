// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(Root);

	//Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(Root);
	DoorMesh->SetRelativeLocation(FVector(0, 0, 10));

	//Set Interaction Trigger
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	BoxComponent->SetBoxExtent(FVector(100, 80, 100));

	InteractionTrigger = BoxComponent;
	InteractionTrigger->SetupAttachment(DoorMesh);
	InteractionTrigger->SetRelativeLocation(FVector(0, 80, 100));


	//Interactable Component
	InteractableComponent = CreateDefaultSubobject<UInteractable>(TEXT("Door Interactable"));


}

void ADoor::FlipFlopDoor()
{
	SetIsOpen(!bIsOpen);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	InitializeInteractableComponent(this, InteractionTrigger, DoorMesh);
	SetIsOpen(bIsOpen);

}


bool ADoor::SetIsOpen(bool isOpen)
{
	if (bIsSealed)isOpen = false;
	bIsOpen = isOpen;

	if (bIsOpen) {

		FQuat DesiredRotation = FQuat::MakeFromEuler(FVector(0, 0, 110));
		DoorMesh->SetRelativeRotation(DesiredRotation, true);
	}
	else {

		DoorMesh->SetRelativeRotation(FRotator::ZeroRotator, true);

	}

	return bIsOpen;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADoor::InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor, UPrimitiveComponent* TrigggerSet, UStaticMeshComponent* MeshSet)
{
	InteractableComponent->Initialize(OwnerActor, TrigggerSet, MeshSet);
	InteractableComponent->OnPlayerInteracted.AddUniqueDynamic(this, &ADoor::FlipFlopDoor);
}

UInteractable* ADoor::GetInteractableComponent()
{
	return InteractableComponent;
}
