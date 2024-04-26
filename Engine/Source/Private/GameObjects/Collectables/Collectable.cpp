#include "GameObjects/Collectables/Collectable.h"

#include "SDL2/SDL_mixer.h"
#include "Game.h"

#define Super Character

Collectable::Collectable()
{
	// Set variables
	m_ScoreValue = 250.0f;

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Tag = "COLLECTABLE";
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
