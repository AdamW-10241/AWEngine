#include "GameStates/Levels/PlayState.h"

#include "Game.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"

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

	m_EnemyFrequency = 3.0f;
	m_EnemySpawnTimer = 1.0f;
}

void PlayState::OnStart()
{
	CreateHUD();
}

void PlayState::OnUpdate(float DeltaTime)
{
	UpdateHUD();
	
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
		float DifficultyScale = Game::GetGame()->GetRandomFloatRange(1.0f, 2.0f);
		Enemy* E = AddGameObject<Enemy>(DifficultyScale, Scale);

		E->SetPlayerRef(m_PlayerRef);

		// Reset the timer
		m_EnemySpawnTimer = m_EnemyFrequency;
	}
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
