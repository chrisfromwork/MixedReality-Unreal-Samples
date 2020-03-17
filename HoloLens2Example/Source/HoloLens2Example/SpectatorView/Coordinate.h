// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.Generated.h"

USTRUCT()
struct FCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FGuid uniqueId;
	UPROPERTY()
	FTransform localToWorld;
	UPROPERTY()
	FDateTime lastUpdate;
	UPROPERTY()
	FString type;
	UPROPERTY()
	FString data;

	FCoordinate()
	{
		uniqueId = FGuid{};
		localToWorld = FTransform{};
		lastUpdate = FDateTime::UtcNow();
		type = TEXT("Unknown");
		data = TEXT("");
	}
};