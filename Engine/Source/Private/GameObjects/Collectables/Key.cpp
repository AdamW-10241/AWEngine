#include "GameObjects/Collectables/Key.h"

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