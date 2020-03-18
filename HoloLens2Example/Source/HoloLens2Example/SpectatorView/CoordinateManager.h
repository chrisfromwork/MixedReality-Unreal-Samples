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
	static void PopulateInstance(UWorld* world, AActor* creator);

	void UpdateCoordinate(const FUserCoordinate& coordinate);
	void RemoveCoordinate(const FGuid& uniqueId);

	UPROPERTY(Replicated, EditAnywhere)
	TMap<FGuid, FUserCoordinate> Coordinates;

protected:
	virtual void BeginPlay() override;
	static ACoordinateManager* instance;
};
