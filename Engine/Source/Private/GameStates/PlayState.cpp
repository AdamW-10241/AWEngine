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
	m_EnemyFrequency(3.0f),
	m_EnemySpawnTimer(1.0f) {}

void PlayState::OnStart()
{
	Super::OnStart();

	Player* P = AddGameObject<Player>();
	P->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		Game::GetGame()->WindowHeightF() - P->ScaledHalfSize()
	});

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	UpdateScore();

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
}

void PlayState::UpdateScore()
{
	std::string ScoreString = "Score: " + std::to_string(Game::GetGame()->m_Score);
	m_ScoreText->SetText(ScoreString.c_str());
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
		m_EnemyFrequency = std::max(0.5f, m_EnemyFrequency - 0.1f);
		
		UpdateFrequencyText();
	}
}

float PlayState::GetRandomFloatRange(float min, float max) const
{
	std::uniform_real_distribution<float> RandNum(min, max);

	return RandNum(RandGenerator);
}
