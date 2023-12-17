#pragma once
#include "PCH.h"

namespace PapyrusPronounFunctions 
{
    // 5 possible values: 0 = he/his, 1 = she/her, 2 = they/them, 3 = multigender, 4 = default
    uint32_t GetActivePronouns(RE::StaticFunctionTag* base);

    // 5 possible inputs: 0 = he/his, 1 = she/her, 2 = they/them, 3 = multigender, 4 = default
    void SetActivePronouns(RE::StaticFunctionTag* base, uint32_t PronounState);

    // outputs: 0 = he / his, 1 = she / her, 2 = they / them, 3 = multigender, 4 = default
    uint32_t GetPreferredPronouns(RE::StaticFunctionTag* base);

    // inputs: 0 = he / his, 1 = she / her, 2 = they / them, 3 = multigender, 4 = default
    void SetPreferredPronouns(RE::StaticFunctionTag* base, uint32_t PronounState);

    // outputs: true if there is an active pronoun override, false otherwise
    bool GetPronounOverrideActive(RE::StaticFunctionTag* base);

    // inputs: true = turn override on, false = turn override off
    void SetPronounOverrideActive(RE::StaticFunctionTag* base, bool OverrideState);

    // returns whether the SKSE plugin is installed and active
    bool IsInstalled(RE::StaticFunctionTag* base);

    bool RegisterFunctions(RE::BSScript::IVirtualMachine* VM);
};  // namespace PapyrusPronounFunctions