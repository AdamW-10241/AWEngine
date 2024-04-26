#pragma once
#include "GameObjects/SpriteObject.h"
#include "SDL2/SDL_mixer.h"

struct Mix_Chunk;

class VisualEffectObject : public SpriteObject {
public:
	VisualEffectObject() :
		m_Length(0.0f),
		m_Loops(0),
		m_LifeTimer(0.0f),
		m_VFX_SFX(nullptr),
		m_SFX_Volume(100) {}

	VisualEffectObject(Mix_Chunk* SFX, uint32_t SFX_Volume) :
		m_Length(0.0f),
		m_Loops(0),
		m_LifeTimer(0.0f),
		m_VFX_SFX(SFX),
		m_SFX_Volume(SFX_Volume) {}

	~VisualEffectObject() = default;

	int m_Loops;

	virtual void Cleanup() override;

protected:
	virtual void OnStart();

	virtual void OnUpdate(float DeltaTime);

	void LifeTimer(float DeltaTime);

protected:
	// Play length of the effect
	float m_Length;

	// Timer to destroy the effect
	float m_LifeTimer;

	// Play sound
	Mix_Chunk* m_VFX_SFX;

	uint32_t m_SFX_Volume;
};