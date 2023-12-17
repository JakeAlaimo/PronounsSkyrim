#include "PronounOverrides.h"
#include "PCH.h"
#include "PronounHooks.h"
#include "SKSE/API.h"

using namespace REL;
using namespace PronounHooks;

namespace PronounOverrides 
{
    PronounProfile PlayerPronouns;

    // This functor houses the core override logic that will be used in place of the standard GetSex call in the places we hook
    struct GetActorPronounsOverride
    {
        EActorPronouns operator()(RE::Actor* Target)
        {
            bool IsTargetPlayer = Target && Target->formID == 7;
            if (!IsTargetPlayer || PlayerPronouns.ActivePronouns == EActorPronouns::Default)
            {
                return OverriddenCall(Target);
            }

            return PlayerPronouns.ActivePronouns;
        }

        Relocation<GetActorPronouns> OverriddenCall;
    };


    // Override functors maintain state for each GetSex call we intercept
    GetActorPronounsOverride GetIsSexOverride;
    GetActorPronounsOverride GetPCIsSexOverride;
    GetActorPronounsOverride SameSexFirstActorOverride;
    GetActorPronounsOverride SameSexSecondActorOverride;
    GetActorPronounsOverride SameSexAsPCFirstActorOverride;
    GetActorPronounsOverride SameSexAsPCSecondActorOverride;

    // Functors need to be wrapped in order to provide the correct function signatures to our trampoline
    EActorPronouns OverrideGetIsSex(RE::Actor* Target) { return GetIsSexOverride(Target); }
    EActorPronouns OverrideGetPCIsSex(RE::Actor* Target) { return GetPCIsSexOverride(Target); }
    EActorPronouns OverrideSameSexFirstActor(RE::Actor* Target) { return SameSexFirstActorOverride(Target); }
    EActorPronouns OverrideSameSexSecondActor(RE::Actor* Target) { return SameSexSecondActorOverride(Target); }
    EActorPronouns OverrideSameSexAsPCFirstActor(RE::Actor* Target) { return SameSexAsPCFirstActorOverride(Target); }
    EActorPronouns OverrideSameSexAsPCSecondActor(RE::Actor* Target) { return SameSexAsPCSecondActorOverride(Target); }

    bool OverrideHooks() 
    {
        SKSE::Trampoline& Trampoline = SKSE::GetTrampoline();
        Trampoline.create(100);

        uint32_t NumHookedAddresses = 0;

        if (uintptr_t GetIsSexHookAddress = GetIsSexHook().address()) 
        {
            GetIsSexOverride.OverriddenCall = Trampoline.write_call<5>(GetIsSexHookAddress, OverrideGetIsSex);
            NumHookedAddresses++;
        }

        if (uintptr_t GetPCIsSexHookAddress = GetPCIsSexHook().address()) 
        {
            GetPCIsSexOverride.OverriddenCall = Trampoline.write_call<5>(GetPCIsSexHookAddress, OverrideGetPCIsSex);
            NumHookedAddresses++;
        }

        if (uintptr_t SameSexFirstActorHookAddress = SameSexFirstActorHook().address()) 
        {
            SameSexFirstActorOverride.OverriddenCall = Trampoline.write_call<5>(SameSexFirstActorHookAddress, OverrideSameSexFirstActor);
            NumHookedAddresses++;
        }

        if (uintptr_t SameSexSecondActorHookAddress = SameSexSecondActorHook().address()) 
        {
            SameSexSecondActorOverride.OverriddenCall = Trampoline.write_call<5>(SameSexSecondActorHookAddress, OverrideSameSexSecondActor);
            NumHookedAddresses++;
        }

        if (uintptr_t SameSexAsPCFirstActorHookAddress = SameSexAsPCFirstActorHook().address())
        {
            SameSexAsPCFirstActorOverride.OverriddenCall = Trampoline.write_call<5>(SameSexAsPCFirstActorHookAddress, OverrideSameSexAsPCFirstActor);
            NumHookedAddresses++;
        }

        if (uintptr_t SameSexAsPCSecondActorHookAddress = SameSexAsPCSecondActorHook().address())
        {
            SameSexAsPCSecondActorOverride.OverriddenCall = Trampoline.write_call<5>(SameSexAsPCSecondActorHookAddress, OverrideSameSexAsPCSecondActor);
            NumHookedAddresses++;
        }

        return (REL::Module::IsAE()) ? NumHookedAddresses == 6 : NumHookedAddresses == 3;
    }
}  // namespace PronounOverrides