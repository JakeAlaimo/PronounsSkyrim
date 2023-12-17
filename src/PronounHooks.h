#pragma once
#include "PCH.h"
#include "REL/Relocation.h"

namespace PronounHooks
{
    typedef EActorPronouns (*GetActorPronouns)(RE::Actor* Target);

    REL::Relocation<GetActorPronouns> GetIsSexHook() noexcept
    {
        if (REL::Module::IsVR()) // No relocation support for these addresses in VR yet
        {
            return REL::Relocation<GetActorPronouns>(REL::Offset(0x2E8CEB));
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(21030, 21480), 0x2B);
    }

    REL::Relocation<GetActorPronouns> GetPCIsSexHook() noexcept 
    {
        if (!REL::Module::IsAE()) 
        {
            return {};
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(42832, 21485), 0x32);
    }

    REL::Relocation<GetActorPronouns> SameSexFirstActorHook() noexcept 
    {
        if (REL::Module::IsVR()) // No relocation support for these addresses in VR yet
        {
            return REL::Relocation<GetActorPronouns>(REL::Offset(0x2E6C19));
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(20979, 21429), 0x49);
    }

    REL::Relocation<GetActorPronouns> SameSexSecondActorHook() noexcept 
    {
        if (REL::Module::IsVR()) // No relocation support for these addresses in VR yet
        {
            return REL::Relocation<GetActorPronouns>(REL::Offset(0x2E6C23));
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(20979, 21429), 0x53);
    }

    REL::Relocation<GetActorPronouns> SameSexAsPCFirstActorHook() noexcept 
    {
        if (!REL::Module::IsAE()) 
        {
            return {};
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(42832, 21432), 0x50);
    }

    REL::Relocation<GetActorPronouns> SameSexAsPCSecondActorHook() noexcept 
    {
        if (!REL::Module::IsAE()) 
        {
            return {};
        }

        return REL::Relocation<GetActorPronouns>(RELOCATION_ID(42832, 21432), 0x5A);
    }
}