#include "Papyrus.h"
#include "PCH.h"
#include "PronounOverrides.h"

namespace PapyrusPronounFunctions 
{
    uint32_t GetActivePronouns(RE::StaticFunctionTag* Base) 
    {
        return PronounOverrides::PlayerPronouns.ActivePronouns; 
    }

    void SetActivePronouns(RE::StaticFunctionTag* Base, uint32_t PronounState) 
    {
        if (PronounState < 0 || PronounState > 4 || PronounState == EActorPronouns::Multigender)  // Multigender is a special case that can't be made directly active
        {
            return;
        }

        PronounOverrides::PlayerPronouns.ActivePronouns = static_cast<EActorPronouns>(PronounState);
    }

    uint32_t GetPreferredPronouns(RE::StaticFunctionTag* Base)
    { 
        return PronounOverrides::PlayerPronouns.PreferredPronouns;
    }

    void SetPreferredPronouns(RE::StaticFunctionTag* Base, uint32_t PronounState)
    {
        if (PronounState < 0 || PronounState > 4) 
        {
            return;
        }

        PronounOverrides::PlayerPronouns.PreferredPronouns = static_cast<EActorPronouns>(PronounState);
    }

    bool GetPronounOverrideActive(RE::StaticFunctionTag* Base)
    {
        return PronounOverrides::PlayerPronouns.OverrideActive;
    }

    void SetPronounOverrideActive(RE::StaticFunctionTag* Base, bool OverrideState)
    {
        PronounOverrides::PlayerPronouns.OverrideActive = OverrideState;
    }

    bool IsInstalled(RE::StaticFunctionTag* Base)
    {
        return true;  // If this fires at all, it's always true
    }

    bool RegisterFunctions(RE::BSScript::IVirtualMachine* VM)
    {
        if (!VM)
        {
            return false;
        }

        VM->RegisterFunction("GetActivePronouns", "PlayerPronouns", GetActivePronouns);
        VM->RegisterFunction("SetActivePronouns", "PlayerPronouns", SetActivePronouns);

        VM->RegisterFunction("GetPreferredPronouns", "PlayerPronouns", GetPreferredPronouns);
        VM->RegisterFunction("SetPreferredPronounsDLL", "PlayerPronouns", SetPreferredPronouns);

        VM->RegisterFunction("GetPronounOverrideActive", "PlayerPronouns", GetPronounOverrideActive);
        VM->RegisterFunction("SetPronounOverrideActive", "PlayerPronouns", SetPronounOverrideActive);

        VM->RegisterFunction("IsInstalled", "PlayerPronouns", IsInstalled);

        return true;
    }
};
