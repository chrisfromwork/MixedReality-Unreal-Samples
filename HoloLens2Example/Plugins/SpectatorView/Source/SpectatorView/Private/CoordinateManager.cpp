// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateManager.h"
#include "UnrealNetwork.h"
#include "DebugHelper.h"
#include "Engine/World.h"

ACoordinateManager* ACoordinateManager::instance = nullptr;

ACoordinateManager::ACoordinateManager() : Super()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority ||
		GetLocalRole() == ROLE_None)
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		// The coordinate manager doesn't appear to replicate if it doesn't have a root component defined.
		auto root = CreateDefaultSubobject<USceneComponent>(FName{ "Root" });
		root->RegisterComponentWithWorld(GetWorld());
		root->SetWorldLocation(FVector{ 0, 0, 0 });
		root->SetWorldRotation(FRotator{ 0, 0, 0 });
		RootComponent = root;
	}
}

void ACoordinateManager::PopulateInstance(UWorld* world)
{
	if (instance == nullptr)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Name = FName{ "CoordinateManager" };
		spawnParams.Owner = nullptr;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
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
}

void ACoordinateManager::BeginDestroy()
{
	Super::BeginDestroy();
	DebugHelper::PrintDebugLog("ACoordinateManager: begin destroy.", 1);
	if (this == instance)
	{
		instance = nullptr;
	}
}

void ACoordinateManager::UpdateCoordinate(const FUserCoordinate& coordinate)
{
	if (GetLocalRole() == ROLE_Authority ||
		GetLocalRole() == ROLE_None)
	{
		Coordinates.Add(coordinate.uniqueId, coordinate);
		FireCoordinateUpdated(coordinate);
	}
	else
	{
		DebugHelper::PrintDebugError(FString::Printf(TEXT("ACoordinateManager:%d: attempted to update coordinate from client, which isn't allowed."), GetLocalRole()), 1);
		return;
	}
}

void ACoordinateManager::RemoveCoordinate(const FGuid& uniqueId)
{
	if (GetLocalRole() == ROLE_Authority ||
		GetLocalRole() == ROLE_None)
	{
		if (Coordinates.Contains(uniqueId))
		{
			Coordinates.Remove(uniqueId);
		}

		FireCoordinateRemoved(uniqueId);
	}
	else
	{
		DebugHelper::PrintDebugError(FString::Printf(TEXT("ACoordinateManager:%d: attempted to update coordinate from client, which isn't allowed."), GetLocalRole()), 1);
		return;
	}
}

void ACoordinateManager::FireCoordinateUpdated_Implementation(const FUserCoordinate& coordinate)
{
	DebugHelper::PrintDebugLog(FString::Printf(TEXT("ACoordinateManager:%d: firing coordinate updated: %s."), (int32)GetLocalRole(), *coordinate.uniqueId.ToString()), 1);
	Coordinates.Add(coordinate.uniqueId, coordinate);
	if (CoordinateUpdated.IsBound())
	{
		CoordinateUpdated.Broadcast(coordinate);
	}
}

bool ACoordinateManager::FireCoordinateUpdated_Validate(const FUserCoordinate& coordinate)
{
	return true;
}

void ACoordinateManager::FireCoordinateRemoved_Implementation(const FGuid& uniqueId)
{
	DebugHelper::PrintDebugLog(FString::Printf(TEXT("ACoordinateManager:%d: firing coordinate removed: %s."), (int32)GetLocalRole(), *uniqueId.ToString()), 1);
	if (Coordinates.Contains(uniqueId))
	{
		Coordinates.Remove(uniqueId);
	}

	if (CoordinateRemoved.IsBound())
	{
		CoordinateRemoved.Broadcast(uniqueId);
	}
}

bool ACoordinateManager::FireCoordinateRemoved_Validate(const FGuid& uniqueId)
{
	return true;
}
