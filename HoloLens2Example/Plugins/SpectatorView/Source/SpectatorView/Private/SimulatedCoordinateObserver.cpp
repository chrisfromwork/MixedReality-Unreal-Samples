// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulatedCoordinateObserver.h"
#include "DebugHelper.h"

USimulatedCoordinateObserver::USimulatedCoordinateObserver()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USimulatedCoordinateObserver::BeginPlay()
{
	Super::BeginPlay();

	if (Cast<APawn>(GetOwner()) != nullptr &&
		Cast<APawn>(GetOwner())->IsLocallyControlled())
	{
		coordinate = FSimulatedCoordinate{};
		coordinate.localToWorld = FTransform
		{
			FVector
			{
				FMath::RandRange(-100.f, 100.f),
				FMath::RandRange(-100.f, 100.f),
				FMath::RandRange(-100.f, 100.f)
			}
		};

		if (OnCoordinateAdded.IsBound())
		{
			OnCoordinateAdded.Broadcast(coordinate);
		}
	}
}

void USimulatedCoordinateObserver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (Cast<APawn>(GetOwner()) != nullptr &&
		Cast<APawn>(GetOwner())->IsLocallyControlled())
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		deltaSinceLastUpdate += DeltaTime;

		if (OnCoordinateUpdated.IsBound() &&
			deltaSinceLastUpdate > deltaBetweenUpdates)
		{
			coordinate.lastUpdate = FDateTime::UtcNow();
			OnCoordinateUpdated.Broadcast(coordinate);
			deltaSinceLastUpdate = 0;
		}
	}
}

