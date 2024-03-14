#include "GameObjects/Background.h"

Background::Background()
{
	// Add background sprite
	AddSprite("Content/NinjaAdventure/Custom Background/Background.png");

	// Set position
	SetPosition({ 640.0f, 360.0f });
}
