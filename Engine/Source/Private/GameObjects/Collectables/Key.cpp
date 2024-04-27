#include "GameObjects/Collectables/Key.h"

#include "Game.h"

Key::Key()
{
	// Set variables
	m_Scale = 5.0f;
	m_Size = 10.0f;

	m_ScoreValue = 2000.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Treasure/GoldKey.png"
	);
}

void Key::PlayFX()
{
	const auto VFX = Game::GetGame()->AddGameObject<VFX_CollectKey>();
	VFX->SetPosition(GetTransform().Position);
	VFX->SetScale(m_Scale);
}
