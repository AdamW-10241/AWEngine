#include "GameStates/PlayState.h"

#include <string>
#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include "GameObjects/Collectable.h"

#include "Debug.h"

#define Super GameState

float PlayState::m_Score = 0.0f;

PlayState::PlayState()
{
	m_SpawnedPlayer = nullptr;
	m_ScoreText = nullptr;
}

void PlayState::OnStart()
{
	Super::OnStart();

	m_SpawnedPlayer = AddGameObject<Player>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetText("Score: 0");
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	m_ScoreText->SetFontColor(0, 255, 0, 255);
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Score Text
	std::string ScoreString = "Score: " + 
		std::to_string(static_cast<int>(std::trunc(PlayState::m_Score))
	);

	m_ScoreText->SetText(ScoreString.c_str());

	// Add more collectables
	for (int i = m_Collectables.size(); i < 10; i++) {
		m_Collectables.push_back(AddGameObject<Collectable>());
	}

	// Add more enemies
	for (int i = m_Enemies.size(); i < 5; i++) {
		m_Enemies.push_back(AddGameObject<Enemy>());
	}
}

void PlayState::OnGarbageCollection()
{
	// Remove collected collectables
	std::erase_if(m_Collectables,
		[](Collectable* Item) {
			if (!Item->IsPendingDestroy()) {
				return false;
			}

			return true; }
	);

	// Remove defeated enemies
	std::erase_if(m_Enemies,
		[](Enemy* Item) {
			if (!Item->IsPendingDestroy()) {
				return false;
			}

			return true; }
	);
}

void PlayState::OnCleanup()
{
	// Destroy collectables
	for (const auto Item : m_Collectables) {
		Item->DestroyObject();
	}

	// Destroy enemies
	for (const auto Item : m_Enemies) {
		Item->DestroyObject();
	}

	Super::OnCleanup();
}
