// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.Collections.Generic;

public class HoloLens2ExampleEditorTarget : TargetRules
{
	public HoloLens2ExampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        ExtraModuleNames.AddRange( new string[] { "HoloLens2Example" } );
	}
}
