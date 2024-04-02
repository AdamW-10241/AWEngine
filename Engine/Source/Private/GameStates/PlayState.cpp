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
	m_SpawnedEnemy = nullptr;
	m_SpawnedPlayer = nullptr;
	m_ScoreText = nullptr;
}

void PlayState::OnStart()
{
	Super::OnStart();

	m_SpawnedEnemy = AddGameObject<Enemy>();
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

	for (const auto Item : m_Collectables) {
		if (Item == nullptr) {
			//m_Collectables.
		}
	}

	if (m_Collectables.size() < 5) {
		m_Collectables.push_back(AddGameObject<Collectable>());
	}
}

void PlayState::OnCleanup()
{
	// Cleanup collectables
	for (const auto Item : m_Collectables) {
		Item->DestroyObject();
	}

	Super::OnCleanup();
}
