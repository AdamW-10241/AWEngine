#include "GameStates/Levels/LevelStateIntro.h"

#include "GameObjects/Player.h"

#include "Game.h"

#define Super PlayState

void LevelStateIntro::OnStart()
{
	ResetScore();

	LoadMusic("Content/Audio/MUSIC_Play.wav");

	SetKeyCollected();

	// Add objects
	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	// Background
	Vector2 BackgroundPosition = {
		HalfWidth,
		HalfHeight
	};

	AddBackground(
		BackgroundPosition,
		1.0f,
		"Content/NinjaAdventure/Custom Background/Background_IntroLevelState.png"
	);

	// Player
	Vector2 PlayerPosition = {
		HalfWidth,
		Game::GetGame()->WindowHeightF() - Game::GetGame()->WindowHeightF() / 10.0f
	};

	AddPlayer(PlayerPosition, 6.0f);

	// Load trigger
	Vector2 LoadTriggerPosition = {
		HalfWidth,
		0.0f
	};

	m_LoadTriggerPosition = LoadTriggerPosition;
	m_NextLevelValue = 1;
	m_DifficultyScaleIncreaseAmount = 0.0f;

	Super::OnStart();
}