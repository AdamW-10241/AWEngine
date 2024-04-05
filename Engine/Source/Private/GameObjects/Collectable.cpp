#include "GameObjects/Collectable.h"
#include "GameStates/PlayState.h"

#define Super Character

#define SCALE 4.0f
#define SIZE (10.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Collectable::Collectable()
{
	// Set variables
	m_ScoreValue = 1000.0f;
	
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

	// Add bounds
	Bounds* CollectableBounds = AddBounds(0.0f, SIZE);
	CollectableBounds->m_OriginOffset = -HALF_SIZE;
	CollectableBounds->m_Tag = "COLLECTABLE";
	CollectableBounds->m_Debug = false;
}

void Collectable::OnStart()
{
	Super::OnStart();

	SetScale(SCALE);
}

void Collectable::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->m_Tag == "PLAYER") {
		// Add score and destroy
		PlayState::AddScore(m_ScoreValue);
		DestroyObject();
	}
}
