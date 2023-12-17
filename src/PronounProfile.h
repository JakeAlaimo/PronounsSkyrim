#pragma once

#include <stdint.h>

enum EActorPronouns : uint32_t
{
    HeHim,
    SheHer,
    TheyThem,
    Multigender,
    Default
};

struct PronounProfile
{
    EActorPronouns PreferredPronouns = EActorPronouns::Default;
    EActorPronouns ActivePronouns = EActorPronouns::Default;
    bool OverrideActive = false;

    void Reset() 
    {
        PreferredPronouns = EActorPronouns::Default;
        ActivePronouns = EActorPronouns::Default;
        bool OverrideActive = false;
    }
};