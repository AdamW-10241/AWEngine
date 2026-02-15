#pragma once
#include "EngineTypes.h"
#include "SDL2/SDL_mixer.h"

enum AW_SoundType {
    AW_SOUND_NONE,
    AW_SOUND_DEATH_STANDARD,
    AW_SOUND_DEATH_PLAYER,
    // Sound Type Number'
    AW_SOUND_NUM
};

class SoundManager {
public:
    // Static reference
    static SoundManager& Get();

    void PlaySound(AW_SoundType soundType = AW_SOUND_NONE);

    void Shutdown();

private:
    SoundManager();

    Mix_Chunk* LoadSound(const char* PathToFile);

    void PrimeSound(AW_SoundType soundType = AW_SOUND_NONE, int volume = 0);

    // Sounds
    TArray<Mix_Chunk*> m_Sounds;
};