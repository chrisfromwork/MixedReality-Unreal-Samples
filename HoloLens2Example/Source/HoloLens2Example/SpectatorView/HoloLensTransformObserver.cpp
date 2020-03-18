// Fill out your copyright notice in the Description page of Project Settings.


#include "HoloLensTransformObserver.h"
#include "DebugHelper.h"

// Sets default values for this component's properties
UHoloLensTransformObserver::UHoloLensTransformObserver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHoloLensTransformObserver::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UHoloLensTransformObserver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (cameraComponent == nullptr)
	{
		cameraComponent = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	}

	//deltaSinceLastCameraMessage += DeltaTime;
	//if (cameraComponent &&
	//	deltaSinceLastCameraMessage > deltaBetweenCameraMessages)
	//{
	//	auto ownerTransform = GetOwner()->GetTransform();
	//	FString ownerTranslationText(L"Translation:");
	//	ownerTranslationText.Append(ownerTransform.GetTranslation().ToString());
	//	FString ownerRotationText(L"Rotation:");
	//	ownerRotationText.Append(ownerTransform.GetRotation().Euler().ToString());
	//	FString ownerScaleText(L"Scale:");
	//	ownerScaleText.Append(ownerTransform.GetScale3D().ToString());

	//	auto cameraTransform = cameraComponent->GetComponentTransform();
	//	FString translationText(L"Translation:");
	//	translationText.Append(cameraTransform.GetTranslation().ToString());
	//	FString rotationText(L"Rotation:");
	//	rotationText.Append(cameraTransform.GetRotation().Euler().ToString());
	//	FString scaleText(L"Scale:");
	//	scaleText.Append(cameraTransform.GetScale3D().ToString());

	//	DebugHelper::PrintDebugLog(scaleText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog(rotationText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog(translationText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog("Camera Transform:", deltaBetweenCameraMessages);

	//	DebugHelper::PrintDebugLog("\n", deltaBetweenCameraMessages);

	//	DebugHelper::PrintDebugLog(ownerScaleText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog(ownerRotationText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog(ownerTranslationText, deltaBetweenCameraMessages);
	//	DebugHelper::PrintDebugLog("Owner Transform:", deltaBetweenCameraMessages);

	//	deltaSinceLastCameraMessage = 0;
	//}
}

