#include <SKSE/Interfaces.h>
#include <SKSE/API.h>
#include "Serialization.h"
#include "Papyrus.h"
#include "PronounOverrides.h"

using namespace SKSE;

namespace 
{
    SKSEPluginLoad(const LoadInterface* SKSE)
    {
        Init(SKSE);

        if (!Serialization::InitializeSerialization())
        {
            return false;
        }

        if (!PronounOverrides::OverrideHooks())
        {
            return false;
        }

        if (auto* PapyrusInterface = GetPapyrusInterface())
        {
            return PapyrusInterface->Register(PapyrusPronounFunctions::RegisterFunctions);
        } 

        return false;
    }
}