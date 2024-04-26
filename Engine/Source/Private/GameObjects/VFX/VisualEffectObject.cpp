#include "GameObjects/VFX/VisualEffectObject.h"

#include "SDL2/SDL_mixer.h"

#define Super SpriteObject

void VisualEffectObject::Cleanup()
{
	// Cleanup weapon SFX
	if (m_VFX_SFX != nullptr) {
		Mix_FreeChunk(m_VFX_SFX);
	}

	Super::Cleanup();
}

void VisualEffectObject::OnStart()
{
	Super::OnStart();
	
	// Get animation time
	for (auto Item : GetAllSprites()) {
		float Frames = static_cast<float>(
			std::max(Item->m_Sprite->GetAnimParams()->EndFrame - Item->m_Sprite->GetAnimParams()->StartFrame, 0U)
		);

		float AnimLength = Frames / std::max(Item->m_Sprite->GetAnimParams()->fps, 0.0000001f);

		if (AnimLength > m_Length) {
			m_Length = AnimLength;
		}
	}

	// Play sound effect
	if (m_VFX_SFX != nullptr) {
		Mix_VolumeChunk(m_VFX_SFX, m_SFX_Volume);
		Mix_PlayChannel(-1, m_VFX_SFX, 0);
	}

	// Set life timer
	m_LifeTimer = m_Length;
}

void VisualEffectObject::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	LifeTimer(DeltaTime);
}

void VisualEffectObject::LifeTimer(float DeltaTime)
{
	// Countdown timer
	m_LifeTimer -= DeltaTime;
	
	// Loop and destroy if timer is over
	if (m_LifeTimer <= 0.0f) {
		if (m_Loops > 0) {
			m_Loops--;
			m_LifeTimer = m_Length;
			return;
		}

		DestroyObject();
	}
}
