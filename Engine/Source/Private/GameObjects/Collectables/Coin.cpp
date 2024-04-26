#include "GameObjects/Collectables/Coin.h"

#include "SDL2/SDL_mixer.h"
#include "Game.h"

Coin::Coin()
{
	// Set variables
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
}