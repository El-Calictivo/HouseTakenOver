// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "EventsSubsystem.generated.h"

template<typename T>
using TEventCallback = TFunction<void(T)>;

UCLASS()
class UEventsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	template<typename T>
	void AddEventListener(TEventCallback<T> Listener);


};

