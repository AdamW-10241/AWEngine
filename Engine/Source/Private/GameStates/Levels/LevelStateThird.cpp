#include "GameStates/Levels/LevelStateThird.h"

#include "GameObjects/Player.h"

#include "Game.h"

#define Super PlayState

void LevelStateThird::OnStart()
{
	LoadMusic("Content/Audio/MUSIC_Play.wav");

	// Add objects
	float Width = Game::GetGame()->WindowWidthF();
	float Height = Game::GetGame()->WindowHeightF();

	float HalfWidth = Width / 2.0f;
	float HalfHeight = Height / 2.0f;

	// Background
	Vector2 BackgroundPosition = {
		HalfWidth,
		HalfHeight
	};

	AddBackground(
		BackgroundPosition,
		0.9f,
		"Content/NinjaAdventure/Custom Background/Background_ThirdLevelState.png"
	);

	// Player
	Vector2 PlayerPosition = {
		HalfWidth,
		Game::GetGame()->WindowHeightF() - Game::GetGame()->WindowHeightF() / 10.0f
	};

	AddPlayer(PlayerPosition, 4.0f);

	// Set enemy spawn positions
	float HeightOffset = Height / 4;
	float WidthOffset = Game::GetGame()->WindowHeightF() / 10.0f;

	m_EnemySpawnPositions[0] = { HalfWidth, 0.0f };
	m_EnemySpawnPositions[1] = { HalfWidth, 0.0f };
	m_EnemySpawnPositions[2] = { WidthOffset, HeightOffset };
	m_EnemySpawnPositions[3] = { Width - WidthOffset, HeightOffset };

	// Set key info
	m_KeySpawnPosition = PlayerPosition;

	// Set trigger info
	Vector2 LoadTriggerPosition = {
		Width * 0.45f,
		0.0f
	};

	m_LoadTriggerPosition = LoadTriggerPosition;
	m_LoadTriggerScale = 2.5f;
	m_NextLevelValue = 1;

	Super::OnStart();
}

void LevelStateThird::OnUpdate(float DeltaTime)
{
	EnemySpawner(DeltaTime, 4.0f);

	Super::OnUpdate(DeltaTime);
}
