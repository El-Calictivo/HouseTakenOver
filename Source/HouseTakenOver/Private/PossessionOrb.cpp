// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessionOrb.h"

// Sets default values
APossessionOrb::APossessionOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APossessionOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APossessionOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

