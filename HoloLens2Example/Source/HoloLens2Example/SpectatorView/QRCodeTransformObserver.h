// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoloLensARFunctionLibrary.h"
#include "ARTrackable.h"
#include "ARTrackableNotifyComponent.h"
#include "HoloLensTransformObserver.h"
#include "QRCode.h"
#include "QRCodeTransformObserver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoordinateDelegate, const FCoordinate&, coordinate);


UCLASS( ClassGroup=(SpectatorView), meta=(BlueprintSpawnableComponent) )
class HOLOLENS2EXAMPLE_API UQRCodeTransformObserver : public UARTrackableNotifyComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQRCodeTransformObserver();

	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate OnCoordinateAdded;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate OnCoordinateUpdated;
	UPROPERTY(BlueprintAssignable, Category = "SpectatorView")
	FCoordinateDelegate OnCoordinateRemoved;

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

	TMap<FGuid, FQRCode> qrCodes;
	TMap<FGuid, AActor*> debugVisuals;

private:
	UFUNCTION()
	void OnImageAdded(UARTrackedImage* image);
	UFUNCTION()
	void OnImageUpdated(UARTrackedImage* image);
	UFUNCTION()
	void OnImageRemoved(UARTrackedImage* image);
};
