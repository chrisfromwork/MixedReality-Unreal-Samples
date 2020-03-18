// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateManager.h"
#include "UnrealNetwork.h"
#include "DebugHelper.h"

ACoordinateManager* ACoordinateManager::instance = nullptr;

ACoordinateManager::ACoordinateManager(class FObjectInitializer const & initializer) : Super(initializer)
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

void ACoordinateManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACoordinateManager, Coordinates);
}

void ACoordinateManager::PopulateInstance(UWorld* world, AActor* creator)
{
	if (instance == nullptr &&
		creator != nullptr &&
		creator->GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Name = FName{ "CoordinateManager" };
		spawnParams.Owner = nullptr;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		ACoordinateManager* manager = world->SpawnActor<ACoordinateManager>(ACoordinateManager::StaticClass(), FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, spawnParams);
		if (manager != nullptr)
		{
			instance = manager;
		}
	}
}

void ACoordinateManager::BeginPlay()
{
	Super::BeginPlay();
	DebugHelper::PrintDebugLog("ACoordinateManager: begin play.", 1);
	SetReplicates(true);
}

void ACoordinateManager::UpdateCoordinate(const FUserCoordinate& coordinate)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		DebugHelper::PrintDebugError(FString::FromInt(GetLocalRole()), 10);
		return;
	}

	DebugHelper::PrintDebugLog("ACoordinateManager: updating coordinate.", 1);
	Coordinates.FindOrAdd(coordinate.uniqueId, coordinate);
}

void ACoordinateManager::RemoveCoordinate(const FGuid& uniqueId)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		DebugHelper::PrintDebugError("ACoordinateManager: attempted to update coordinate from client, which isn't allowed.", 10);
		return;
	}

	DebugHelper::PrintDebugLog("ACoordinateManager: removing coordinate.", 1);
	if (Coordinates.Contains(uniqueId))
	{
		Coordinates.Remove(uniqueId);
	}
}
