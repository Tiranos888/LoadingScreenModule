// (c) 2021 Sonic Terror

using UnrealBuildTool;

public class LoadingScreen : ModuleRules
{
    public LoadingScreen(ReadOnlyTargetRules Target) : base(Target) 
    {
        PrivatePCHHeaderFile = "LoadingScreen.h";

        bUsePrecompiled = true;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add("LoadingScreen/");

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "MoviePlayer",
                "Slate",
                "SlateCore",
                "InputCore",
                "BattleTest"
            }
        );

    }
}