#include "Serialization.h"
#include "PCH.h"
#include "PronounOverrides.h"

namespace Serialization 
{
    enum SerializationVersion : uint32_t
    {
        PreCommonLib = 1,
        ActivePreferredAndOverride = 2, // Post-commonlib, the basic 3 pieces of data this mod started with

        // Alias to end of the enum
        LastPlusOne,
        Last = LastPlusOne - 1
    };

    void Revert(SKSE::SerializationInterface* Interface)  // between save loads, revert to default value
    {
        PronounOverrides::PlayerPronouns.Reset();
    }

    void Save(SKSE::SerializationInterface* Interface)
    {
        if (Interface && Interface->OpenRecord('DATA', SerializationVersion::Last))
        {
            Interface->WriteRecordData(&PronounOverrides::PlayerPronouns.ActivePronouns, sizeof(DWORD));
            Interface->WriteRecordData(&PronounOverrides::PlayerPronouns.PreferredPronouns, sizeof(DWORD));
            Interface->WriteRecordData(&PronounOverrides::PlayerPronouns.OverrideActive, sizeof(bool));
        }
    }

    void Load(SKSE::SerializationInterface* Interface)
    {
        uint32_t Type;
        uint32_t Version;
        uint32_t Length;

        while (Interface && Interface->GetNextRecordInfo(Type, Version, Length)) 
        {
            if (Type != 'DATA' || !Length)
            {
                continue;
            }

            if (Version <= SerializationVersion::ActivePreferredAndOverride)
            {
                Interface->ReadRecordData(&PronounOverrides::PlayerPronouns.ActivePronouns, sizeof(DWORD));
                Interface->ReadRecordData(&PronounOverrides::PlayerPronouns.PreferredPronouns, sizeof(DWORD));
                Interface->ReadRecordData(&PronounOverrides::PlayerPronouns.OverrideActive, sizeof(bool));
            }
        }
    }

    bool InitializeSerialization() 
    {
        auto* Serialization = SKSE::GetSerializationInterface();

        if (!Serialization) 
        {
            return false;
        }

        Serialization->SetUniqueID(0xCC5E6E19);

        Serialization->SetRevertCallback(Revert);
        Serialization->SetSaveCallback(Save);
        Serialization->SetLoadCallback(Load);

        return true;
    }
}  // namespace Serialization