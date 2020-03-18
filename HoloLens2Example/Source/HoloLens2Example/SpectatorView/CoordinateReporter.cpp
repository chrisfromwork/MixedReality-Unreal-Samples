// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateReporter.h"
#include "GameFramework/PlayerState.h"
#include "CoordinateManager.h"
#include "DebugHelper.h"

UCoordinateReporter::UCoordinateReporter()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoordinateReporter::BeginPlay()
{
	Super::BeginPlay();
	auto pawn = Cast<APawn>(GetOwner());
	if (pawn != nullptr)
	{
		PlayerId = Cast<APawn>(GetOwner())->GetPlayerState()->PlayerId;
	}
	else
	{
		PlayerId = -1;
		DebugHelper::PrintDebugError(TEXT("failed to locate pawn owner of UCoordinateReporter"), 10);
	}

	auto qrCodeObserver = Cast<UQRCodeTransformObserver>(GetOwner()->GetComponentByClass(UQRCodeTransformObserver::StaticClass()));
	if (qrCodeObserver)
	{
		qrCodeObserver->OnCoordinateAdded.AddDynamic(this, &UCoordinateReporter::OnCoordinateAdded);
		qrCodeObserver->OnCoordinateUpdated.AddDynamic(this, &UCoordinateReporter::OnCoordinateUpdated);
		qrCodeObserver->OnCoordinateRemoved.AddDynamic(this, &UCoordinateReporter::OnCoordinateRemoved);
	}
	else
	{
		DebugHelper::PrintDebugError(TEXT("failed to locate qr code observer for UCoordinateReporter"), 10);
	}
}

void UCoordinateReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCoordinateReporter::OnCoordinateAdded(const FCoordinate& coordinate)
{
	if (ACoordinateManager::Instance() != nullptr)
	{
		ACoordinateManager::Instance()->UpdateCoordinate(FUserCoordinate{ PlayerId, coordinate });
	}
}

void UCoordinateReporter::OnCoordinateUpdated(const FCoordinate& coordinate)
{
	if (ACoordinateManager::Instance() != nullptr)
	{
		ACoordinateManager::Instance()->UpdateCoordinate(FUserCoordinate{ PlayerId, coordinate });
	}
}

void UCoordinateReporter::OnCoordinateRemoved(const FCoordinate& coordinate)
{
	if (ACoordinateManager::Instance() != nullptr)
	{
		ACoordinateManager::Instance()->RemoveCoordinate(coordinate.uniqueId);
	}
}
