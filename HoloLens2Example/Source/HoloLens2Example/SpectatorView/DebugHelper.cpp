// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void DebugHelper::PrintDebugLog(FString text, float displayTime)
{
	GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::White, text);
}
