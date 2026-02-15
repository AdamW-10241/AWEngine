#include "SoundManager.h"
#include "Debug.h"

SoundManager& SoundManager::Get()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlaySound(Mix_Chunk* chunk)
{
	if (chunk) {
		Mix_PlayChannel(-1, chunk, 0);
	}
}

Mix_Chunk* SoundManager::LoadSound(const char* PathToFile)
{
	Mix_Chunk* chunk = Mix_LoadWAV(PathToFile);
	if (!chunk) {
		AW_LOG("SoundManager", "Failed to load sound: " + std::string(PathToFile));
		AW_LOG("SoundManager", "Error Log: " + std::string(Mix_GetError()));
	}
	return chunk;
}
