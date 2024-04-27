#include "GameObjects/Collectables/Collectable.h"

#include "SDL2/SDL_mixer.h"
#include "Game.h"

#define Super Character

Collectable::Collectable()
{
	// Set variables
	m_ScoreValue = 250.0f;
}

void Collectable::OnStart()
{
	SetScale(m_Scale);
	
	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Tag = "COLLECTABLE";
	m_Bounds->m_Debug = true;
}

void Collectable::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Collect if touching player
	if (strcmp(OverlapBounds->m_Tag, "PLAYER") == 0) {
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
