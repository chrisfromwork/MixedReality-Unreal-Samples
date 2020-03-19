// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.Generated.h"

USTRUCT(BlueprintType)
struct FCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FGuid uniqueId;
	UPROPERTY(EditAnywhere)
	FTransform localToWorld;
	UPROPERTY(EditAnywhere)
	FDateTime lastUpdate;
	UPROPERTY(EditAnywhere)
	FString type;
	UPROPERTY(EditAnywhere)
	FString data;

	FCoordinate()
	{
		uniqueId = FGuid::NewGuid();
		localToWorld = FTransform{};
		lastUpdate = FDateTime::UtcNow();
		type = TEXT("Unknown");
		data = TEXT("");
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoordinateDelegate, const FCoordinate&, coordinate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoordinateIdDelegate, const FGuid&, coordinate);

class ICoordinateObserver
{
public:
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate OnCoordinateAdded;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate OnCoordinateUpdated;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateIdDelegate OnCoordinateRemoved;
};