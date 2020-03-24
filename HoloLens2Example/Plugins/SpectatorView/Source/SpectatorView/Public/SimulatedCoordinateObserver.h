// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Coordinate.h"
#include "SimulatedCoordinateObserver.generated.h"

USTRUCT(BlueprintType)
struct FSimulatedCoordinate : public FCoordinate
{
	GENERATED_USTRUCT_BODY()

	FSimulatedCoordinate() : FCoordinate()
	{
		type = TEXT("Simulated");
	}
};

UCLASS( ClassGroup=(SpectatorView), meta=(BlueprintSpawnableComponent) )
class SPECTATORVIEW_API USimulatedCoordinateObserver : public UActorComponent, public ICoordinateObserver
{
	GENERATED_BODY()

public:	
	USimulatedCoordinateObserver();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	FSimulatedCoordinate coordinate;
	float deltaBetweenUpdates = 1.0f;
	float deltaSinceLastUpdate = 0.0f;
};
