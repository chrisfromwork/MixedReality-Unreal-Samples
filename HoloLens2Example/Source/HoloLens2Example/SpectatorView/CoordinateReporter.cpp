// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateReporter.h"
#include "GameFramework/PlayerState.h"
#include "CoordinateManager.h"
#include "QRCodeObserver.h"
#include "SimulatedCoordinateObserver.h"
#include "DebugHelper.h"
#include "UnrealNetwork.h"

UCoordinateReporter::UCoordinateReporter() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoordinateReporter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCoordinateReporter, PlayerId);
}

void UCoordinateReporter::BeginPlay()
{
	Super::BeginPlay();
	PlayerId = InvalidPlayerId;
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

				if (pawn->IsLocallyControlled())
				{
					auto qrCodeObserver = Cast<UQRCodeObserver>(GetOwner()->GetComponentByClass(UQRCodeObserver::StaticClass()));
					if (qrCodeObserver)
					{
						qrCodeObserver->OnCoordinateAdded.AddDynamic(this, &UCoordinateReporter::OnCoordinateAdded);
						qrCodeObserver->OnCoordinateUpdated.AddDynamic(this, &UCoordinateReporter::OnCoordinateUpdated);
						qrCodeObserver->OnCoordinateRemoved.AddDynamic(this, &UCoordinateReporter::OnCoordinateRemoved);
					}
					else
					{
						DebugHelper::PrintDebugError(FString::Printf(TEXT("UCoordinateReporter:%d: Failed to find UQRCodeObserver"), PlayerId), 10);
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
						DebugHelper::PrintDebugError(FString::Printf(TEXT("UCoordinateReporter:%d: Failed to find USimulatedCoordinateObserver"), PlayerId), 10);
					}
				}
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

void UCoordinateReporter::OnCoordinateRemoved(const FGuid& uniqueId)
{
	CoordinateRemovedImpl(uniqueId);
}

void UCoordinateReporter::CoordinateUpdatedImpl_Implementation(const FCoordinate& coordinate)
{
	if (ACoordinateManager::Instance() == nullptr)
	{
		ACoordinateManager::PopulateInstance(GetWorld());
	}

	if (ACoordinateManager::Instance() != nullptr &&
		PlayerId != InvalidPlayerId)
	{
		DebugHelper::PrintDebugLog(FString::Printf(TEXT("UCoordinateReporter:%d: reporting coordinate update."), PlayerId), 1);
		ACoordinateManager::Instance()->UpdateCoordinate(FUserCoordinate{ PlayerId, coordinate });
	}
}

bool UCoordinateReporter::CoordinateUpdatedImpl_Validate(const FCoordinate& coordinate)
{
	return true;
}

void UCoordinateReporter::CoordinateRemovedImpl_Implementation(const FGuid& uniqueId)
{
	if (PlayerId != InvalidPlayerId)
	{
		DebugHelper::PrintDebugLog(FString::Printf(TEXT("UCoordinateReporter:%d: reporting coordinate removed."), PlayerId), 1);
		ACoordinateManager::Instance()->RemoveCoordinate(uniqueId);
	}
}

bool UCoordinateReporter::CoordinateRemovedImpl_Validate(const FGuid& uniqueId)
{
	return true;
}
