#include "GameObjects/Collectables/Coin.h"

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
		false,
		&AnimParams
	);
}

void Coin::PlayFX()
{
	const auto VFX = Game::GetGame()->AddGameObject<VFX_CollectCoin>();
	VFX->SetPosition(GetTransform().Position);
	VFX->SetScale(m_Scale);
}
