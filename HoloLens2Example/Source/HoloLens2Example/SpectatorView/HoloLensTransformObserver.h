// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "HoloLensTransformObserver.generated.h"

UCLASS( ClassGroup = (SpectatorView), meta = (BlueprintSpawnableComponent) )
class HOLOLENS2EXAMPLE_API UHoloLensTransformObserver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoloLensTransformObserver();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UCameraComponent* cameraComponent;

private:
	float deltaSinceLastCameraMessage = 0;
	float deltaBetweenCameraMessages = 0.25f;
};
