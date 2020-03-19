// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserCoordinate.h"
#include "CoordinateManager.generated.h"

UCLASS()
class HOLOLENS2EXAMPLE_API ACoordinateManager : public AActor
{
	GENERATED_BODY()

public:
	static ACoordinateManager* Instance() { return instance; }
	static void PopulateInstance(UWorld* world);

	ACoordinateManager();

	void UpdateCoordinate(const FUserCoordinate& coordinate);
	void RemoveCoordinate(const FGuid& uniqueId);

	UPROPERTY(EditAnywhere, Category = "SpectatorView")
	TMap<FGuid, FUserCoordinate> Coordinates;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate CoordinateUpdated;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateIdDelegate CoordinateRemoved;

protected:
	static ACoordinateManager* instance;

	virtual void BeginPlay() override;
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void FireCoordinateUpdated(const FUserCoordinate& coordinate);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void FireCoordinateRemoved(const FGuid& uniqueId);
};
