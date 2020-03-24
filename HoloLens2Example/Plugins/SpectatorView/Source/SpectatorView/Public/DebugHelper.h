// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SPECTATORVIEW_API DebugHelper
{
public:
	static void SetDebugLogEnabled(bool value);
	static void PrintDebugLog(FString text, float displayTime);
	static void PrintDebugError(FString text, float displayTime);
	static bool TryCreateDebugVisual(UWorld* world, AActor*& actor);

private:
	static bool logEnabled;
};
