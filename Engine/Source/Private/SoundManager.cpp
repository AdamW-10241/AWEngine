#include "SoundManager.h"
#include "Debug.h"

SoundManager::SoundManager() {
	// Initialise sound bank
	m_Sounds.resize(AW_SOUND_NUM, nullptr);
	Mix_AllocateChannels(32);

	// Setup Sounds
	m_Sounds[AW_SOUND_DEATH_STANDARD] = LoadSound("Content/Audio/DEATH_SFX_DC.wav");
	PrimeSound(AW_SOUND_DEATH_STANDARD, 15);

	m_Sounds[AW_SOUND_DEATH_PLAYER] = LoadSound("Content/Audio/DEATH_SFX_PLAYER.wav");
	PrimeSound(AW_SOUND_DEATH_PLAYER, 100);
}

void SoundManager::Shutdown()
{
	// Cleanup SFX
	Mix_HaltChannel(-1);

	for (auto Sound : m_Sounds) {
		if (Sound != nullptr) {
			Mix_FreeChunk(Sound);
		}
	}

	Mix_CloseAudio();
}

SoundManager& SoundManager::Get()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlaySound(AW_SoundType soundType)
{
	if (soundType == AW_SOUND_NONE) return;

	// Play sound
	if (m_Sounds[soundType]) {
		Mix_PlayChannel(-1, m_Sounds[soundType], 0);
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

void SoundManager::PrimeSound(AW_SoundType soundType, int volume)
{
	Mix_VolumeChunk(m_Sounds[soundType], 0);
	int channel = Mix_PlayChannel(-1, m_Sounds[soundType], 0);
	if (channel != -1) Mix_HaltChannel(channel);
	Mix_VolumeChunk(m_Sounds[soundType], volume);
}
