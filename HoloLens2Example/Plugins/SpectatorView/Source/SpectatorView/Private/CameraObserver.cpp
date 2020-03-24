// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraObserver.h"
#include "DebugHelper.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

// Sets default values for this component's properties
UCameraObserver::UCameraObserver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCameraObserver::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCameraObserver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (cameraComponent == nullptr)
	{
		cameraComponent = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	}
}

