// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

bool DebugHelper::logEnabled = true;

void DebugHelper::SetDebugLogEnabled(bool value)
{
	logEnabled = value;
}

void DebugHelper::PrintDebugLog(FString text, float displayTime)
{
	if (logEnabled)
	{
		GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::White, text);
	}
}

void DebugHelper::PrintDebugError(FString text, float displayTime)
{
	GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Red, text);
}

bool DebugHelper::TryCreateDebugVisual(UWorld* world, AActor*& actor)
{
	actor = nullptr;
	UObject* spawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/SpectatorView/BP_DebugVisual")));
	if (!spawnActor)
	{
		DebugHelper::PrintDebugError(TEXT("Failed to find debug visual: /SpectatorView/BP_DebugVisual"), 15);
		return false;
	}

	UBlueprint* debugVisualBluePrint = Cast<UBlueprint>(spawnActor);
	if (!debugVisualBluePrint)
	{
		DebugHelper::PrintDebugError(TEXT("Debug visual was loaded but wasn't a blueprint."), 15);
		return false;
	}
	
	// This originally used spawnActor
	UClass* bluePrintClass = debugVisualBluePrint->StaticClass();
	if (bluePrintClass == NULL)
	{
		DebugHelper::PrintDebugError(TEXT("Debug visual blueprint class was null."), 15);
		return false;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = nullptr;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	actor = world->SpawnActor<AActor>(debugVisualBluePrint->GeneratedClass, FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, spawnParams);
	return true;
}
