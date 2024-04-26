#include "GameObjects/Collectables/Key.h"

#include "SDL2/SDL_mixer.h"
#include "Game.h"

Key::Key()
{
	// Set variables
	m_Scale = 3.5f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Treasure/GoldKey.png"
	);

	// Set the scale
	SetScale(m_Scale);
}