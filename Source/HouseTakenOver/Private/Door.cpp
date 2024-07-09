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

	//Set Arrow
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Door Anchor"));
	ArrowComponent->SetArrowLength(100);
	ArrowComponent->SetupAttachment(Root);


	//Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetRelativeRotation(FVector(0, 90, 0).ToOrientationRotator());
	DoorMesh->SetRelativeLocation(FVector(55, 5, 0));
	DoorMesh->SetupAttachment(ArrowComponent);

	//Set Interaction Trigger
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	BoxComponent->SetBoxExtent(FVector(120, 140, 110));

	InteractionTrigger = BoxComponent;
	InteractionTrigger->SetupAttachment(DoorMesh);
	InteractionTrigger->SetRelativeLocation(FVector(0, 0, 110));
	InteractionTrigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	InteractionTrigger->SetGenerateOverlapEvents(true);


	//Interactable Component
	InteractableComponent = CreateDefaultSubobject<UInteractable>(TEXT("Door Interactable"));
	InteractableComponent->SetCollider(BoxComponent);

}

void ADoor::FlipFlopDoor()
{
	SetIsOpen(!bIsOpen);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	SetIsOpen(bIsOpen);
	InteractableComponent->OnPlayerInteracted.AddUniqueDynamic(this, &ADoor::FlipFlopDoor);
}


bool ADoor::SetIsOpen(bool isOpen)
{
	bIsOpen = isOpen;

	if (bIsOpen) {

		ArrowComponent->SetRelativeRotation(FVector(0, 100, 0).ToOrientationRotator(), true);
	}
	else {

		ArrowComponent->SetRelativeRotation(FVector(0, 0, 0).ToOrientationRotator(), true);

	}

	return bIsOpen;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

