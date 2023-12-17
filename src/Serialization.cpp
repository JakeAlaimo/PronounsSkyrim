#include "Serialization.h"
#include "PCH.h"
#include "PronounOverrides.h"

namespace Serialization 
{
    constexpr float SerializationDataVersion = 1.1;

    void Revert(SKSE::SerializationInterface* Interface)  // between save loads, revert to default value
    {
        PronounOverrides::PlayerPronouns.Reset();
    }

    void Save(SKSE::SerializationInterface* Interface)
    {
        if (Interface && Interface->OpenRecord('DATA', SerializationDataVersion))
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
            if (Type != 'DATA')
            {
                continue;
            }

            if (Version == SerializationDataVersion && Length)
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