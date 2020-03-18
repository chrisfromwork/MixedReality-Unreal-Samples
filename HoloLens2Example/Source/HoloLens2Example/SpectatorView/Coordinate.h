// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.Generated.h"

USTRUCT(BlueprintType)
struct FCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGuid uniqueId;
	UPROPERTY(BlueprintReadWrite)
	FTransform localToWorld;
	UPROPERTY(BlueprintReadWrite)
	FDateTime lastUpdate;
	UPROPERTY(BlueprintReadWrite)
	FString type;
	UPROPERTY(BlueprintReadWrite)
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