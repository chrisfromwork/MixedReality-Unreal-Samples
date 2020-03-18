// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateManager.h"
#include "UnrealNetwork.h"
#include "DebugHelper.h"

ACoordinateManager* ACoordinateManager::instance = nullptr;

ACoordinateManager::ACoordinateManager(class FObjectInitializer const & initializer) : Super(initializer)
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
	instance = this;
}

void ACoordinateManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACoordinateManager, Coordinates);
}

void ACoordinateManager::UpdateCoordinate_Implementation(const FUserCoordinate& coordinate)
{
	//FString coordinateText(L"Coordinate:");
	//coordinateText.Append(coordinate.uniqueId.ToString());
	//coordinateText.Append(",");
	//coordinateText.Append(FString::FromInt(coordinate.playerId));
	//coordinateText.Append(",");
	//coordinateText.Append(coordinate.localToWorld.ToString());
	//DebugHelper::PrintDebugError(coordinateText, 10);
	Coordinates.FindOrAdd(coordinate.uniqueId, coordinate);
}

bool ACoordinateManager::UpdateCoordinate_Validate(const FUserCoordinate& coordinate)
{
	return true;
}

void ACoordinateManager::RemoveCoordinate_Implementation(const FGuid& uniqueId)
{
	if (Coordinates.Contains(uniqueId))
	{
		Coordinates.Remove(uniqueId);
	}
}

bool ACoordinateManager::RemoveCoordinate_Validate(const FGuid& uniqueId)
{
	return true;
}
