// Fill out your copyright notice in the Description page of Project Settings.


#include "QRCodeTransformObserver.h"
#include "DebugHelper.h"

// Sets default values for this component's properties
UQRCodeTransformObserver::UQRCodeTransformObserver()
{
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

// Called every frame
void UQRCodeTransformObserver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	qrCodes[qrCode->UniqueId] = QRCode{ qrCode, localToWorld };
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
	qrCodes[qrCode->UniqueId] = QRCode{ qrCode, localToWorld };
	UpdateDebugVisual(qrCode->UniqueId, localToWorld);
}

void UQRCodeTransformObserver::OnQRCodeRemoved(UARTrackedQRCode* qrCode)
{
	FString qrText(L"QRCode Removed:");
	qrText.Append(qrCode->QRCode);
	qrText.Append(", ");
	qrText.Append(qrCode->UniqueId.ToString());
	DebugHelper::PrintDebugLog(qrText, 1);

	if (qrCodes.count(qrCode->UniqueId) != 0)
	{
		qrCodes.erase(qrCode->UniqueId);
	}

	DestroyDebugVisual(qrCode->UniqueId);
}

void UQRCodeTransformObserver::UpdateDebugVisual(const FGuid& uniqueId, const FTransform& localToWorld)
{
	AActor* debugVisual;
	if (debugVisuals.count(uniqueId) != 0)
	{
		debugVisual = debugVisuals[uniqueId];
	}
	else if(DebugHelper::TryCreateDebugVisual(GetOwner()->GetWorld(), debugVisual))
	{
		debugVisuals[uniqueId] = debugVisual;
	}

	if (debugVisual)
	{
		debugVisual->SetActorTransform(localToWorld);
	}
}

void UQRCodeTransformObserver::DestroyDebugVisual(const FGuid& uniqueId)
{
	if (debugVisuals.count(uniqueId) != 0)
	{
		debugVisuals.erase(uniqueId);
	}
}
