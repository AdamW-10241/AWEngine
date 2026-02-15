#pragma once
#include "EngineTypes.h"
#include "SDL2/SDL_mixer.h"

class SoundManager {
public:
    // Static reference
    static SoundManager& Get();

    void PlaySound(Mix_Chunk* chunk);

    Mix_Chunk* LoadSound(const char* PathToFile);

private:
    SoundManager() {}
};

// Cleanup SFX
//for (auto Item : m_DC_SFX) {
//	if (Item != nullptr) {
//		Mix_FreeChunk(Item);
//	}
//}