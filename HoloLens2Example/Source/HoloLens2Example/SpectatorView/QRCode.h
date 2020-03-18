// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.h"
#include "ARTrackable.h"
#include "QRCode.Generated.h"

USTRUCT(BlueprintType)
struct FQRCode : public FCoordinate
{
	GENERATED_USTRUCT_BODY()

	FQRCode() : FCoordinate()
	{
		type = TEXT("QRCode");
	}

	FQRCode(const UARTrackedQRCode* qrCode, const FTransform& transform) : FCoordinate()
	{
		uniqueId = qrCode->UniqueId;
		localToWorld = transform;
		lastUpdate = FDateTime::UtcNow();
		type = TEXT("QRCode");
		data = qrCode->QRCode;
	}
};