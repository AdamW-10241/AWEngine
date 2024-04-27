#include "GameStates/Levels/PlayState.h"

#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include "GameObjects/Collectables/Key.h"
#include "GameObjects/HUD.h"

#include <random>

#include "Debug.h"

#define Super GameState

PlayState::PlayState() {
	m_HUD = nullptr;

	m_PlayerRef = nullptr;

	m_EndPlayTimer = 3.0f;

	m_EnemyFrequency = 4.0f;
	m_EnemySpawnTimer = 1.0f;
	
	m_BasePauseTimer = 1.0f;
	m_PauseTimer = 0.0f;

	m_DifficultyScale = 1.0f;
	m_DifficultyScaleIncreaseAmount = 0.1f;

	m_EnemiesKilled = 0;
	m_KeyRequirement = 5;
	m_KeySpawned = false;
	m_KeySpawnPosition = { 0.0f };
	m_KeyCollected = false;

	m_NextLevelValue = 0;

	m_LoadTrigger = nullptr;
	m_LoadTriggerPosition = { 0.0f };
	m_LoadTriggerScale = 1.0f;
	m_TriggerActive = false;

	m_CanPause = true;
}

void PlayState::OnStart()
{
	ScaleDifficulty();
	
	CreateHUD();

	AddLoadTrigger();
}

void PlayState::OnUpdate(float DeltaTime)
{
	CheckKeySpawn();

	CheckTriggerSpawn();

	UpdatePauseTimer(DeltaTime);

	CheckEndGame(DeltaTime);
}

void PlayState::OnCleanup()
{
	// Cleanup
	m_PlayerRef->DestroyObject();
}

void PlayState::AddBackground(Vector2 Position, float Scale, const char* PathToFile)
{
	// Add background
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite(PathToFile);
	m_Background->SetPosition(Position);
	m_Background->SetScale(Scale);
}

void PlayState::AddPlayer(Vector2 Position, float Scale)
{
	// Add player
	m_PlayerRef = AddGameObject<Player>(Scale);
	m_PlayerRef->SetPosition(Position);
}

void PlayState::CheckEndGame(float DeltaTime)
{
	// Check player health
	if (m_PlayerRef->GetHealth() <= 0.0f) {
		// If dead then decrease timer
		m_EndPlayTimer -= DeltaTime;

		// Change to game over state at end of timer
		if (m_EndPlayTimer <= 0.0f) {
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(new GameOverState());
		}
	}
}

void PlayState::CheckKeySpawn()
{
	if (!m_KeySpawned && m_EnemiesKilled >= m_KeyRequirement) {
		// Spawn key
		const auto SpawnedKey = AddGameObject<Key>();
		SpawnedKey->SetPosition(m_KeySpawnPosition);

		m_KeySpawned = !m_KeySpawned;
	}
}

void PlayState::CheckTriggerSpawn()
{
	if (m_KeyCollected && !m_TriggerActive) {
		// Spawn load trigger
		m_LoadTrigger->SetActive();

		m_TriggerActive = !m_TriggerActive;
	}
}

void PlayState::ScaleDifficulty()
{
	// Scale difficulty
	m_KeyRequirement = int((float)m_KeyRequirement * m_DifficultyScale);

	m_EnemyFrequency = std::fmaxf(m_EnemyFrequency / m_DifficultyScale, 1.0f);
}

void PlayState::EnemySpawner(float DeltaTime, float Scale)
{
	// Countdown spawn timer
	m_EnemySpawnTimer -= DeltaTime;

	// Check timer
	if (m_EnemySpawnTimer <= 0.0f) {
		// Spawn Enemy
		Enemy* SpawnedEnemy = AddGameObject<Enemy>(m_DifficultyScale, Scale);
		SpawnedEnemy->SetPlayerRef(m_PlayerRef);
		SpawnedEnemy->SetPosition(m_EnemySpawnPositions[rand() % 4]);

		// Reset the timer
		m_EnemySpawnTimer = m_EnemyFrequency;
	}
}

void PlayState::AddLoadTrigger()
{
	// Add trigger
	m_LoadTrigger = AddGameObject<LoadTrigger>(
		m_NextLevelValue, 
		m_DifficultyScale + m_DifficultyScaleIncreaseAmount,
		m_LoadTriggerScale
	);
	m_LoadTrigger->SetPosition(m_LoadTriggerPosition);
}

void PlayState::AddKey(Vector2 Position)
{	
	// Add key
	const auto SpawnedKey = Game::GetGame()->Game::AddGameObject<Key>();
	SpawnedKey->SetPosition(Position);
}

void PlayState::ResetScore()
{
	Game::GetGame()->m_Score = 0;
}

void PlayState::CreateHUD()
{
	// Create HUD objects
	m_HUD = AddGameObject<HUD>(m_PlayerRef);
}