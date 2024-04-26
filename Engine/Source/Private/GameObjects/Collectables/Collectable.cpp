#include "GameObjects/Collectables/Collectable.h"
#include "GameObjects/VFX/VFX_CollectableCollect.h"

#include "SDL2/SDL_mixer.h"
#include "Game.h"

#define Super Character

Collectable::Collectable()
{
	// Set variables
	m_ScoreValue = 250.0f;
	m_C_SFX = nullptr;

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Tag = "COLLECTABLE";
}

void Collectable::Cleanup()
{
	// Cleanup weapon SFX
	if (m_C_SFX != nullptr) {
		Mix_FreeChunk(m_C_SFX);
	}
	
	Super::Cleanup();
}

void Collectable::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Collect if touching player
	if (OverlapBounds->m_Tag == "PLAYER") {
		// Add score
		Game::GetGame()->m_Score += m_ScoreValue;
		
		// Collect collectable
		CollectCollectable();

		// Play FX
		PlayFX();

		// Destroy collectable
		DestroyObject();
	}
}

void Collectable::PlayFX()
{
	// VFX
	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_CollectableCollect>();
	VFX->SetPosition(GetTransform().Position);
	VFX->SetScale(m_Scale * 0.5f);

	// SFX
	if (m_C_SFX != nullptr) {
		Mix_PlayChannel(-1, m_C_SFX, 0);
	}
}
