// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoloLensARFunctionLibrary.h"
#include "ARTrackable.h"
#include "ARTrackableNotifyComponent.h"
#include <map>
#include <chrono>
#include "QRCodeTransformObserver.generated.h"

struct Coordinate
{
	FGuid uniqueId;
	FTransform localToWorld;
	std::chrono::system_clock::time_point lastUpdate;
	FString type;
	FString data;

	Coordinate()
	{
		uniqueId = FGuid{};
		localToWorld = FTransform{};
		lastUpdate = std::chrono::system_clock::now();
		type = TEXT("Unknown");
		data = TEXT("");
	}
};

struct QRCode : Coordinate
{
	QRCode() : Coordinate()
	{
		type = TEXT("QRCode");
	}

	QRCode(const UARTrackedQRCode* qrCode, const FTransform& transform) : Coordinate()
	{
		uniqueId = qrCode->UniqueId;
		localToWorld = transform;
		lastUpdate = std::chrono::system_clock::now();
		type = TEXT("QRCode");
		data = qrCode->QRCode;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLOLENS2EXAMPLE_API UQRCodeTransformObserver : public UARTrackableNotifyComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQRCodeTransformObserver();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnQRCodeAdded(UARTrackedQRCode* qrCode);
	virtual void OnQRCodeUpdated(UARTrackedQRCode* qrCode);
	virtual void OnQRCodeRemoved(UARTrackedQRCode* qrCode);
	void UpdateDebugVisual(const FGuid& uniqueId, const FTransform& localToWorld);
	void DestroyDebugVisual(const FGuid& uniqueId);
	
	UPROPERTY(VisibleAnywhere)
	FRotator QRCodeRotation = FRotator{ 180, 90, 0 };

	std::map<FGuid, Coordinate> qrCodes;
	std::map<FGuid, AActor*> debugVisuals;

private:
	UFUNCTION()
	void OnImageAdded(UARTrackedImage* image);
	UFUNCTION()
	void OnImageUpdated(UARTrackedImage* image);
	UFUNCTION()
	void OnImageRemoved(UARTrackedImage* image);
};
