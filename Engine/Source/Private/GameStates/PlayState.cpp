#include "GameStates/PlayState.h"

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

// Initialise a random generator
std::default_random_engine RandGenerator;

PlayState::PlayState() :
	m_ScoreText(nullptr),
	m_FreqText(nullptr),
	m_PlayerLivesText(nullptr),
	m_PlayerLives(-1),
	m_PlayerRef(nullptr),
	m_EndPlayTimer(3.0f),
	m_MinEnemyFrequency(0.5f),
	m_MaxEnemyFrequency(3.0f),
	m_EnemyFrequency(m_MaxEnemyFrequency),
	m_EnemySpawnTimer(1.0f) {}

void PlayState::OnStart()
{
	Super::OnStart();

	Game::GetGame()->m_Score = 0;

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

	m_PlayerLivesText = AddGameObject<TextObject>();
	m_PlayerLivesText->SetPosition({
		10.0f,
		Game::GetGame()->WindowHeightF() - 10.0f
	});
	m_PlayerLivesText->SetFontSize(35);
	m_PlayerLivesText->SetAligment(AL_BOTTOM_LEFT);
	UpdateLives();

	m_FreqText = AddGameObject<TextObject>();
	m_FreqText->SetPosition({ 10.0f, 55.0f });
	m_FreqText->SetFontSize(25);
	m_FreqText->SetAligment(AL_TOP_LEFT);
	UpdateFrequencyText();

	// Set the seed of random to the current calendar time
	RandGenerator.seed(time(nullptr));
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	EnemySpawner(DeltaTime);

	UpdateScore();

	if (m_PlayerLives <= 0) {
		m_EndPlayTimer -= DeltaTime;

		if (m_EndPlayTimer <= 0.0f) {
			auto NewState = new MainMenuState();
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(NewState);
		}
	}

	UpdateLives();
}

void PlayState::UpdateScore()
{
	int Score = Game::GetGame()->m_Score;
	
	std::string ScoreString = "Score: " + std::to_string(Score);
	m_ScoreText->SetText(ScoreString.c_str());
}

void PlayState::UpdateLives()
{
	int Lives = m_PlayerRef->GetLives();

	if (Lives != m_PlayerLives) {
		m_PlayerLives = Lives;

		std::string LivesString = "Lives: " + std::to_string(m_PlayerLives);
		m_PlayerLivesText->SetText(LivesString.c_str());
	}
}

void PlayState::UpdateFrequencyText()
{
	// Create a string stream that converts a float into a less precise version
	// Set precision is the number of decimal places to see
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_EnemyFrequency;

	std::string FreqString = "Enemy Spawn Time: " + stream.str();
	m_FreqText->SetText(FreqString.c_str());
}

void PlayState::EnemySpawner(float DeltaTime)
{
	// Countdown timer
	m_EnemySpawnTimer -= DeltaTime;

	// If the timer reaches 0 then spawn an enemy
	if (m_EnemySpawnTimer <= 0.0f) {
		Enemy* E = AddGameObject<Enemy>();

		float PosX = GetRandomFloatRange(
			E->ScaledHalfSize(),
			Game::GetGame()->WindowWidthF() - E->ScaledHalfSize()
		);

		E->SetPosition({ PosX, -E->ScaledHalfSize() });

		// Reset the timer
		m_EnemySpawnTimer = m_EnemyFrequency;
		// Reduce the next spawn frequency
		m_EnemyFrequency = std::max(m_MinEnemyFrequency, m_EnemyFrequency - 0.1f);
		
		UpdateFrequencyText();
	}
}

float PlayState::GetRandomFloatRange(float min, float max) const
{
	std::uniform_real_distribution<float> RandNum(min, max);

	return RandNum(RandGenerator);
}
