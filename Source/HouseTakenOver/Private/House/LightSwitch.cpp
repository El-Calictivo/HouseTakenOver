// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"
#include <Components/BoxComponent.h>
#include "Interactions/Interactable.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(Root);

	//Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));

	//Set Interaction Trigger
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	BoxComponent->SetBoxExtent(FVector(200, 50, 50));

	InteractionTrigger = BoxComponent;
	InteractionTrigger->SetupAttachment(Mesh);
	InteractionTrigger->SetRelativeLocation(FVector(150, 0, 0));


	//Interactable Component
	InteractableComponent = CreateDefaultSubobject<UInteractable>(TEXT("Door Interactable"));
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	InitializeInteractableComponent(this);
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitch::InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor)
{
	InteractableComponent->Initialize(OwnerActor);
	InteractableComponent->OnPlayerInteracted.AddUniqueDynamic(this, &ALightSwitch::FlipFlopPower);
}

void ALightSwitch::SetPowered(bool bNewIsOn)
{

	for (AActor* Light : ConnectedLights) {
		if (!Light)continue;
		Light->SetActorHiddenInGame(!Light->IsHidden());
	}

}

void ALightSwitch::FlipFlopPower()
{

	SetPowered(false);
}

