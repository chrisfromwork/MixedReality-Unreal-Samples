// Fill out your copyright notice in the Description page of Project Settings.


#include "QRCodeTransformObserver.h"
#include "DebugHelper.h"

// Sets default values for this component's properties
UQRCodeTransformObserver::UQRCodeTransformObserver()
{
	// TODO - test whether a tick is needed for detection
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UQRCodeTransformObserver::BeginPlay()
{
	Super::BeginPlay();
	OnAddTrackedImage.AddDynamic(this, &UQRCodeTransformObserver::OnImageAdded);
	OnUpdateTrackedImage.AddDynamic(this, &UQRCodeTransformObserver::OnImageUpdated);
	OnRemoveTrackedImage.AddDynamic(this, &UQRCodeTransformObserver::OnImageRemoved);
	UHoloLensARFunctionLibrary::StartQRCodeCapture();
}

void UQRCodeTransformObserver::OnImageAdded(UARTrackedImage* image)
{
	auto qrCode = Cast<UARTrackedQRCode>(image);
	if (qrCode)
	{
		OnQRCodeAdded(qrCode);
	}
}

void UQRCodeTransformObserver::OnImageUpdated(UARTrackedImage* image)
{
	auto qrCode = Cast<UARTrackedQRCode>(image);
	if (qrCode)
	{
		OnQRCodeUpdated(qrCode);
	}
}

void UQRCodeTransformObserver::OnImageRemoved(UARTrackedImage* image)
{
	auto qrCode = Cast<UARTrackedQRCode>(image);
	if (qrCode)
	{
		OnQRCodeRemoved(qrCode);
	}
}

void UQRCodeTransformObserver::OnQRCodeAdded(UARTrackedQRCode* qrCode)
{
	FString qrText(L"QRCode Added:");
	qrText.Append(qrCode->QRCode);
	qrText.Append(", ");
	qrText.Append(qrCode->UniqueId.ToString());
	DebugHelper::PrintDebugLog(qrText, 1);

	FTransform localToWorld = FTransform{ QRCodeRotation } * qrCode->GetLocalToWorldTransform();
	qrCodes.FindOrAdd(qrCode->UniqueId, FQRCode{ qrCode, localToWorld });

	if (OnCoordinateAdded.IsBound())
	{
		OnCoordinateAdded.Broadcast(qrCodes[qrCode->UniqueId]);
	}

	UpdateDebugVisual(qrCode->UniqueId, localToWorld);
}

void UQRCodeTransformObserver::OnQRCodeUpdated(UARTrackedQRCode* qrCode)
{
	FString qrText(L"QRCode Updated:");
	qrText.Append(qrCode->QRCode);
	qrText.Append(", ");
	qrText.Append(qrCode->UniqueId.ToString());
	DebugHelper::PrintDebugLog(qrText, 1);

	FTransform localToWorld = FTransform{ QRCodeRotation } *qrCode->GetLocalToWorldTransform();
	qrCodes.FindOrAdd(qrCode->UniqueId, FQRCode{ qrCode, localToWorld });

	if (OnCoordinateUpdated.IsBound())
	{
		OnCoordinateUpdated.Broadcast(qrCodes[qrCode->UniqueId]);
	}

	FString coordinateText(L"Coordinate:");
	coordinateText.Append(qrCodes[qrCode->UniqueId].uniqueId.ToString());
	coordinateText.Append(",");
	coordinateText.Append(qrCode->UniqueId.ToString());
	DebugHelper::PrintDebugError(coordinateText, 10);
	UpdateDebugVisual(qrCode->UniqueId, localToWorld);
}

void UQRCodeTransformObserver::OnQRCodeRemoved(UARTrackedQRCode* qrCode)
{
	FString qrText(L"QRCode Removed:");
	qrText.Append(qrCode->QRCode);
	qrText.Append(", ");
	qrText.Append(qrCode->UniqueId.ToString());
	DebugHelper::PrintDebugLog(qrText, 1);

	if (qrCodes.Contains(qrCode->UniqueId))
	{
		if (OnCoordinateRemoved.IsBound())
		{
			OnCoordinateRemoved.Broadcast(qrCodes[qrCode->UniqueId]);
		}

		qrCodes.Remove(qrCode->UniqueId);
	}

	DestroyDebugVisual(qrCode->UniqueId);
}

void UQRCodeTransformObserver::UpdateDebugVisual(const FGuid& uniqueId, const FTransform& localToWorld)
{
	AActor* debugVisual;
	if (debugVisuals.Contains(uniqueId))
	{
		debugVisual = debugVisuals[uniqueId];
	}
	else if(DebugHelper::TryCreateDebugVisual(GetOwner()->GetWorld(), debugVisual))
	{
		debugVisuals.FindOrAdd(uniqueId, debugVisual);
	}

	if (debugVisual)
	{
		debugVisual->SetActorTransform(localToWorld);
	}
}

void UQRCodeTransformObserver::DestroyDebugVisual(const FGuid& uniqueId)
{
	if (debugVisuals.Contains(uniqueId))
	{
		debugVisuals.Remove(uniqueId);
	}
}
