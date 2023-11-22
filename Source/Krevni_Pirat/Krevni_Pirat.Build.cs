// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Krevni_Pirat : ModuleRules
{
	public Krevni_Pirat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AnimGraphRuntime" });
	}
}
