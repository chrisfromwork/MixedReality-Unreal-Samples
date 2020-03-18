// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UserCoordinate.h"
#include "CoordinateReporter.generated.h"


UCLASS( ClassGroup=(SpectatorView), meta=(BlueprintSpawnableComponent) )
class HOLOLENS2EXAMPLE_API UCoordinateReporter : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:	
	UCoordinateReporter();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 PlayerId;
	const int32 InvalidPlayerId = -1;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnCoordinateAdded(const FCoordinate& coordinate);
	UFUNCTION()
	void OnCoordinateUpdated(const FCoordinate& coordinate);
	UFUNCTION()
	void OnCoordinateRemoved(const FCoordinate& coordinate);

	UFUNCTION(Server, Reliable, WithValidation)
	void CoordinateUpdatedImpl(const FCoordinate& coordinate);
	UFUNCTION(Server, Reliable, WithValidation)
	void CoordinateRemovedImpl(const FCoordinate& coordinate);
};
