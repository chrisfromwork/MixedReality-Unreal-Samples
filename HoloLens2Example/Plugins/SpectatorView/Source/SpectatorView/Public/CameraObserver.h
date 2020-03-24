// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraObserver.generated.h"

UCLASS( ClassGroup = (SpectatorView), meta = (BlueprintSpawnableComponent) )
class SPECTATORVIEW_API UCameraObserver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraObserver();
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
