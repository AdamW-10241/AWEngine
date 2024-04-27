#include "GameStates/Levels/PlayState.h"

#include "Game.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include "GameObjects/Collectables/Key.h"

#include <string>
#include <iomanip>
#include <random>
#include <sstream>

#include "Debug.h"

#define Super GameState

PlayState::PlayState() {
	m_ScoreText = nullptr;
	m_PlayerHealthText = nullptr;

	m_PlayerHealth = -1.0f;
	m_PlayerRef = nullptr;

	m_EndPlayTimer = 3.0f;

	m_EnemyFrequency = 4.0f;
	m_EnemySpawnTimer = 1.0f;

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
}

void PlayState::OnStart()
{
	ScaleDifficulty();
	
	CreateHUD();

	AddLoadTrigger();
}

void PlayState::OnUpdate(float DeltaTime)
{
	UpdateHUD();
	
	CheckKeySpawn();

	CheckTriggerSpawn();

	CheckEndGame(DeltaTime);
}

void PlayState::OnCleanup()
{
	// Cleanup
	m_PlayerRef->DestroyObject();
	m_ScoreText->DestroyObject();
	m_PlayerHealthText->DestroyObject();
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
	if (m_PlayerHealth <= 0.0f) {
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

void PlayState::UpdateScore()
{
	int Score = Game::GetGame()->m_Score;
	
	std::stringstream stream;
	stream << std::fixed << Score;

	std::string ScoreString = stream.str();
	m_ScoreText->SetText(ScoreString.c_str());
}

void PlayState::UpdateHealth()
{
	float Health = m_PlayerRef->GetHealth();

	if (Health != m_PlayerHealth) {
		// Update health
		m_PlayerHealth = Health;

		// Use a stream to set float text precision
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << m_PlayerHealth;

		std::string HealthString = "Health: " + stream.str();
		m_PlayerHealthText->SetText(HealthString.c_str());
	}
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
	float ScreenWidth = Game::GetGame()->WindowWidthF();
	float ScreenHeight = Game::GetGame()->WindowHeightF();
	float Offset = ScreenHeight / 40.0f;

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ ScreenWidth - Offset, Offset });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetAligment(AL_TOP_RIGHT);

	m_PlayerHealthText = AddGameObject<TextObject>();
	m_PlayerHealthText->SetPosition({ Offset, Offset});
	m_PlayerHealthText->SetFontSize(35);
	m_PlayerHealthText->SetAligment(AL_TOP_LEFT);

	UpdateHUD();
}

void PlayState::UpdateHUD()
{
	// Update HUD
	UpdateScore();

	UpdateHealth();
}
