// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoloLensARFunctionLibrary.h"
#include "ARTrackable.h"
#include "ARTrackableNotifyComponent.h"
#include <map>
#include "QRCodeTransformObserver.generated.h"


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
	
	std::map<FString, std::map<FGuid, UARTrackedQRCode*>> qrCodes;

private:
	UFUNCTION()
	void OnImageAdded(UARTrackedImage* image);
	UFUNCTION()
	void OnImageUpdated(UARTrackedImage* image);
	UFUNCTION()
	void OnImageRemoved(UARTrackedImage* image);
};
