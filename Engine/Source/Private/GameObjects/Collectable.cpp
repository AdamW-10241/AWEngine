#include "GameObjects/Collectable.h"
#include "GameStates/PlayState.h"
#include "Game.h"

#define Super Character

Collectable::Collectable()
{
	// Set variables
	m_ScoreValue = 200.0f;
	m_ScoreValue = 250.0f;

	m_Scale = 3.5f;
	m_Size = 10.0f;

	// Main sprite
	AnimationParams AnimParams;
	AnimParams.fps = 12;
	AnimParams.FrameHeight = 10;
	AnimParams.FrameWidth = 10;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Treasure/Coin2.png",
		&AnimParams
	);

	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	Bounds* CollectableBounds = AddBounds(0.0f, ScaledSize());
	CollectableBounds->m_OriginOffset = -ScaledHalfSize();
	CollectableBounds->m_Tag = "COLLECTABLE";
	CollectableBounds->m_Debug = false;
}

void Collectable::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->m_Tag == "PLAYER") {
		// Add score and destroy
		Game::GetGame()->m_Score += m_ScoreValue;
		// FX???
		DestroyObject();
	}
}
