// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DDakji : ModuleRules
{
	public DDakji(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // 슬레이트, UMG 사용을 위해서
        PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
