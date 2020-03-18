// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateReporter.h"
#include "GameFramework/PlayerState.h"
#include "CoordinateManager.h"
#include "QRCodeObserver.h"
#include "SimulatedCoordinateObserver.h"
#include "DebugHelper.h"

UCoordinateReporter::UCoordinateReporter(class FObjectInitializer const& initializer) : Super(initializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoordinateReporter::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->SetReplicates(true);
	PlayerId = InvalidPlayerId;

	auto qrCodeObserver = Cast<UQRCodeObserver>(GetOwner()->GetComponentByClass(UQRCodeObserver::StaticClass()));
	if (qrCodeObserver)
	{
		qrCodeObserver->OnCoordinateAdded.AddDynamic(this, &UCoordinateReporter::OnCoordinateAdded);
		qrCodeObserver->OnCoordinateUpdated.AddDynamic(this, &UCoordinateReporter::OnCoordinateUpdated);
		qrCodeObserver->OnCoordinateRemoved.AddDynamic(this, &UCoordinateReporter::OnCoordinateRemoved);
	}
	else
	{
		DebugHelper::PrintDebugError(TEXT("UCoordinateReporter: Failed to find UQRCodeObserver"), 10);
	}

	auto simulatedCoordinateObserver = Cast<USimulatedCoordinateObserver>(GetOwner()->GetComponentByClass(USimulatedCoordinateObserver::StaticClass()));
	if (simulatedCoordinateObserver)
	{
		simulatedCoordinateObserver->OnCoordinateAdded.AddDynamic(this, &UCoordinateReporter::OnCoordinateAdded);
		simulatedCoordinateObserver->OnCoordinateUpdated.AddDynamic(this, &UCoordinateReporter::OnCoordinateUpdated);
		simulatedCoordinateObserver->OnCoordinateRemoved.AddDynamic(this, &UCoordinateReporter::OnCoordinateRemoved);
	}
	else
	{
		DebugHelper::PrintDebugError(TEXT("UCoordinateReporter: Failed to find USimulatedCoordinateObserver"), 10);
	}
}

void UCoordinateReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PlayerId == InvalidPlayerId)
	{
		auto pawn = Cast<APawn>(GetOwner());
		if (pawn != nullptr)
		{
			auto playerState = pawn->GetPlayerState();
			if (playerState != nullptr)
			{
				PlayerId = playerState->PlayerId;
			}
			else
			{
				PlayerId = InvalidPlayerId;
			}
		}
		else
		{
			PlayerId = InvalidPlayerId;
		}
	}
}

void UCoordinateReporter::OnCoordinateAdded(const FCoordinate& coordinate)
{
	CoordinateUpdatedImpl(coordinate);
}

void UCoordinateReporter::OnCoordinateUpdated(const FCoordinate& coordinate)
{
	CoordinateUpdatedImpl(coordinate);
}

void UCoordinateReporter::OnCoordinateRemoved(const FCoordinate& coordinate)
{
	CoordinateRemovedImpl(coordinate);
}

void UCoordinateReporter::CoordinateUpdatedImpl_Implementation(const FCoordinate& coordinate)
{
	if (ACoordinateManager::Instance() == nullptr)
	{
		ACoordinateManager::PopulateInstance(GetWorld(), GetOwner());
	}

	if (ACoordinateManager::Instance() != nullptr &&
		PlayerId != InvalidPlayerId)
	{
		DebugHelper::PrintDebugLog("UCoordinateReporter: reporting coordinate update.", 1);
		ACoordinateManager::Instance()->UpdateCoordinate(FUserCoordinate{ PlayerId, coordinate });
	}
	else if (PlayerId == InvalidPlayerId)
	{
		DebugHelper::PrintDebugError(TEXT("Unable to report coordinate based on invalid player id"), 10);
	}
}

bool UCoordinateReporter::CoordinateUpdatedImpl_Validate(const FCoordinate& coordinate)
{
	return true;
}

void UCoordinateReporter::CoordinateRemovedImpl_Implementation(const FCoordinate& coordinate)
{
	if (PlayerId != InvalidPlayerId)
	{
		DebugHelper::PrintDebugLog(TEXT("UCoordinateReporter: reporting coordinate removed."), 1);
		ACoordinateManager::Instance()->RemoveCoordinate(coordinate.uniqueId);
	}
}

bool UCoordinateReporter::CoordinateRemovedImpl_Validate(const FCoordinate& coordinate)
{
	return true;
}
