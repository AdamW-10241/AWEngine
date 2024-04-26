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
	m_FreqText = nullptr;
	m_PlayerHealthText = nullptr;
	m_BGM = Mix_LoadMUS("Content/Audio/MUSIC_Play.wav");
	m_PlayerHealth = -1.0f;
	m_PlayerRef = nullptr;
	m_EndPlayTimer = 3.0f;

	m_EnemyFrequency = 3.0f;
	m_EnemySpawnTimer = 1.0f;
}

void PlayState::OnStart()
{
	Super::OnStart();

	Game::GetGame()->m_Score = 0;

	// Add objects
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/NinjaAdventure/Custom Background/Background_PlayState.png");
	m_Background->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		Game::GetGame()->WindowHeightF() / 2.0f }
	);
	m_Background->SetScale(0.9f);

	m_PlayerRef = AddGameObject<Player>();
	m_PlayerRef->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		 Game::GetGame()->WindowHeightF() - m_PlayerRef->ScaledHalfSize()
	});

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	UpdateScore();

	m_PlayerHealthText = AddGameObject<TextObject>();
	m_PlayerHealthText->SetPosition({
		10.0f,
		Game::GetGame()->WindowHeightF() - 10.0f
	});
	m_PlayerHealthText->SetFontSize(35);
	m_PlayerHealthText->SetAligment(AL_BOTTOM_LEFT);
	UpdateHealth();

	m_FreqText = AddGameObject<TextObject>();
	m_FreqText->SetPosition({ 10.0f, 55.0f });
	m_FreqText->SetFontSize(25);
	m_FreqText->SetAligment(AL_TOP_LEFT);
	UpdateFrequencyText();
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	EnemySpawner(DeltaTime);

	UpdateScore();

	if (m_PlayerHealth <= 0.0f) {
		m_EndPlayTimer -= DeltaTime;

		if (m_EndPlayTimer <= 0.0f) {
			// Change to game over state
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(new GameOverState());
		}
	}

	UpdateHealth();
}

void PlayState::OnCleanup()
{
	m_Background->DestroyObject();
	m_PlayerRef->DestroyObject();
	m_ScoreText->DestroyObject();
	m_PlayerHealthText->DestroyObject();
	m_FreqText->DestroyObject();
}

void PlayState::UpdateScore()
{
	int Score = Game::GetGame()->m_Score;
	
	std::string ScoreString = "Score: " + std::to_string(Score);
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

void PlayState::UpdateFrequencyText()
{
	// Use a stream to set float text precision
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_EnemyFrequency;

	std::string FreqString = "Enemy Spawn Time: " + stream.str();
	m_FreqText->SetText(FreqString.c_str());
}

void PlayState::EnemySpawner(float DeltaTime)
{
	// Countdown spawn timer
	m_EnemySpawnTimer -= DeltaTime;

	// Check timer
	if (m_EnemySpawnTimer <= 0.0f) {
		// Spawn Enemy
		float DifficultyScale = Game::GetGame()->GetRandomFloatRange(1.0f, 2.0f);
		Enemy* E = AddGameObject<Enemy>(DifficultyScale);

		E->SetPlayerRef(m_PlayerRef);

		// Reset the timer
		m_EnemySpawnTimer = m_EnemyFrequency;
		
		UpdateFrequencyText();
	}
}
