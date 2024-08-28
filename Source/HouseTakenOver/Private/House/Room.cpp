// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Door.h"
#include <Subsystems/HouseGraspSubsystem.h>
#include "Components/PostProcessComponent.h"
#include "Components/BoxComponent.h"

#include "Selection.h"
// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(Root);

	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Room Bounds"));
	BoxComponent->SetBoxExtent(FVector(250, 250, 135));
	RoomBounds = BoxComponent;
	RoomBounds->SetupAttachment(Root);

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Processing Volume"));
	PostProcessComponent->Priority = 100;
	PostProcessComponent->bUnbound = false;
	PostProcessComponent->Settings.bOverride_ColorSaturation = true;
	PostProcessComponent->SetupAttachment(RoomBounds);


}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UHouseGraspSubsystem>()->RegisterRoom(this);

	for (ADoor* Door : ConnectedDoors)
	{
		if (!Door)continue;
		Door->OnDoorStateChanged.AddUniqueDynamic(this, &ARoom::OnDoorStateChanged);
	}

}

void ARoom::OnGraspedLevelChanged(float GraspLevel)
{

	float InvertedValue = DesaturationPostVfxCurve ? DesaturationPostVfxCurve->GetFloatValue(GraspLevel) : 1 - GraspLevel;

	FPostProcessSettings& Settings = PostProcessComponent->Settings;
	Settings.ColorSaturation = FVector4(InvertedValue, InvertedValue, InvertedValue, InvertedValue);

}

bool ARoom::IsLocked()
{


	for (ADoor* Door : ConnectedDoors)
	{
		if (!Door)continue;
		if (Door->GetState() != EDoorState::SEALED) return false;

	}
	return true;
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	DrawAdjacentRoomsConnectionNodes();
	DrawConnectedDoorNodes();
#endif
}



void ARoom::IncreaseGraspLevel(float GraspAmount)
{
	if (RoomState == ERoomState::SEALED || RoomState == ERoomState::TAKEN)return;
	if (GraspedLevel >= GraspLevelLimit)return;

	float OldGraspedLevel = GraspedLevel;
	GraspedLevel += GraspAmount;

	if (GraspedLevel >= GraspLevelLimit) {

		GraspedLevel = GraspLevelLimit;
		SetRoomState(ERoomState::TAKEN);

		for (ADoor* Door : ConnectedDoors)
		{
			if (Door)Door->SetDoorState(EDoorState::TAKEN);

		}
	}

	OnGraspLevelChanged.Broadcast(this, OldGraspedLevel, GraspedLevel);
	OnGraspedLevelChanged(GraspedLevel);

}

void ARoom::SetRoomState(ERoomState NewRoomState)
{
	if (RoomState == NewRoomState)return;
	ERoomState OldState = RoomState;
	RoomState = NewRoomState;
	OnRoomStateChanged.Broadcast(this, OldState, RoomState);
}

ERoomState ARoom::GetRoomState() const
{
	return RoomState;
}

#if WITH_EDITOR
void ARoom::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	DrawAdjacentRoomsConnectionNodes(0.1);
	DrawConnectedDoorNodes(3);
}

void ARoom::DrawAdjacentRoomsConnectionNodes(const float Lifetime)
{
	if (!bDegugLines)return;
	if (GEditor->GetSelectedActors()->IsSelected(this))
	{
		for (auto& AdjacencyInfo : AdjacentRooms) {
			if (!AdjacencyInfo.Key)continue;
			FVector StartPoint = GetActorLocation(); // Replace with your start point
			FVector EndPoint = AdjacencyInfo.Key->GetActorLocation(); // Replace with your end point
			float Proximity = AdjacencyInfo.Value.ProximityInfluenceModifier;

			FColor LineColor;
			if (Proximity > .85)LineColor = FColor::Green;
			else if (Proximity >= .7)LineColor = FColor::Turquoise;
			else if (Proximity >= .5)LineColor = FColor::Yellow;
			else if (Proximity > .3)LineColor = FColor::Orange;
			else LineColor = FColor::Red;


			DrawDebugLine(GetWorld(), StartPoint, EndPoint, LineColor, false, -1, 0, Proximity * 15);

		}
	}
}
void ARoom::DrawConnectedDoorNodes(const float Lifetime)
{

	if (!bDegugLines)return;
	if (GEditor->GetSelectedActors()->IsSelected(this))
	{
		for (auto Door : ConnectedDoors) {
			if (!Door)continue;
			FVector StartPoint = GetActorLocation(); // Replace with your start point
			FVector EndPoint = Door->GetActorLocation(); // Replace with your end point

			DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Blue, false, -1, 0, 2);
			DrawDebugSphere(GetWorld(), EndPoint, 20, 6, FColor::Blue, false, -1, 0, 15);

		}
	}


}
#endif



void ARoom::OnDoorStateChanged(EDoorState NewDoorState)
{
	if (IsLocked())SetRoomState(ERoomState::SEALED);

}





