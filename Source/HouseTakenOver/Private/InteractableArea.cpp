// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableArea.h"
#include "Components/BoxComponent.h"
// Sets default values
AInteractableArea::AInteractableArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

}

// Called when the game starts or when spawned
void AInteractableArea::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractableArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableArea::SetIsFocused(bool bSetIsFocused)
{
	this->bIsFocused = bSetIsFocused;
}

