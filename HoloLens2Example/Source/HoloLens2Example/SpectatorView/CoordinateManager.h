// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserCoordinate.h"
#include "CoordinateManager.generated.h"

UCLASS()
class HOLOLENS2EXAMPLE_API ACoordinateManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	ACoordinateManager();
	static ACoordinateManager* Instance() { return instance; }

	UFUNCTION(Server, Reliable, WithValidation)
	void UpdateCoordinate(const FUserCoordinate& coordinate);
	UFUNCTION(Server, Reliable, WithValidation)
	void RemoveCoordinate(const FGuid& uniqueId);

	UPROPERTY(Replicated, EditAnywhere)
	TMap<FGuid, FUserCoordinate> Coordinates;

protected:
	static ACoordinateManager* instance;
};
