// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.h"
#include "UserCoordinate.generated.h"

USTRUCT(BlueprintType)
struct FUserCoordinate : public FCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int32 playerId;

	FUserCoordinate() : FCoordinate()
	{
		playerId = -1;
	}

	FUserCoordinate(const int32& id, const FCoordinate& coordinate) : FCoordinate(coordinate)
	{
		playerId = id;
	}
};