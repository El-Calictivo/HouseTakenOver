// Fill out your copyright notice in the Description page of Project Settings.


#include "House/Window.h"
#include "Interactions/Interactable.h"
#include "House/Room.h"
#include <Components/BoxComponent.h>


// Sets default values
AWindow::AWindow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(Root);

	//Mesh
	WindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window Mesh"));
	WindowMesh->SetupAttachment(Root);


	//Set Interaction Trigger
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	BoxComponent->SetBoxExtent(FVector(30, 15, 54));

	InteractionCollider = BoxComponent;
	InteractionCollider->SetupAttachment(WindowMesh);


	//Interactable Component
	InteractableComponent = CreateDefaultSubobject<UInteractable>(TEXT("Window Interactable"));
}

// Called when the game starts or when spawned
void AWindow::BeginPlay()
{
	Super::BeginPlay();
	InitializeInteractableComponent(this);
	SetState(WindowState);
}


void AWindow::SetState(const EWindowState NewState)
{
	const EWindowState OldState = WindowState;
	WindowState = NewState;

	switch (NewState)
	{
	case EWindowState::OPEN:
	case EWindowState::TAKEN:
		if (Room) Room->OnGraspLevelChanged.RemoveDynamic(this, &AWindow::OnRoomGraspLevelChanged);

		break;
	case EWindowState::CLOSED:
		if (Room) Room->OnGraspLevelChanged.AddUniqueDynamic(this, &AWindow::OnRoomGraspLevelChanged);

		break;
	}

	OnWindowStateChanged(OldState, NewState);

}

void AWindow::InitializeInteractableComponent(TScriptInterface<IInteractableActor> OwnerActor)
{
	InteractableComponent->Initialize(OwnerActor);
	InteractableComponent->OnPlayerInteracted.AddUniqueDynamic(this, &AWindow::CloseWindow);
}



void AWindow::CloseWindow()
{
	if (WindowState == EWindowState::OPEN) OnWindowStateChanged(WindowState, EWindowState::CLOSED);

}

void AWindow::IncreaseRoomGrasp(float GraspAmount)
{
	if (WindowState != EWindowState::OPEN || !Room)return;
	Room->IncreaseGraspLevel(GraspAmount);

}



void AWindow::OnRoomGraspLevelChanged(ARoom* ChangedRoom, float OldGraspLevel, float NewGraspLevel)
{
	if (WindowState != EWindowState::CLOSED) {
		if (ChangedRoom) ChangedRoom->OnGraspLevelChanged.RemoveDynamic(this, &AWindow::OnRoomGraspLevelChanged);
		return;
	}

	if (TryOpeningWindow())SetState(EWindowState::OPEN);

}

bool AWindow::TryOpeningWindow() const
{
	return 	FMath::RandRange(0.0f, 1.0f) <= ReopeningChance;

}

// Called every frame
void AWindow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->GetEngineSubsystem<UEventsSubsystem>()->AddEventListener<FEventBase>(&AWindow::Function);

}


