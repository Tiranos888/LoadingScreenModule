#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class ILoadingScreen : public IModuleInterface
{
public:
    static inline ILoadingScreen& Get() 
    {
        return FModuleManager::LoadModuleChecked<ILoadingScreen>("LoadingScreen");
    }

    virtual void ShowLoadingScreen(bool bManualStop, float TimeSpan) = 0;

    virtual void CloseLoadingScreen() = 0;

};
