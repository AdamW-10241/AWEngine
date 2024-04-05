#include "GameStates/PlayState.h"

#include <string>
#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include "GameObjects/Collectable.h"
#include "Math/Vector2.h"

#include "Debug.h"

#define Super GameState

float PlayState::m_Score = 0.0f;

PlayState::PlayState()
{
	m_SpawnedPlayer = nullptr;
	m_ScoreText = nullptr;
}

void PlayState::SpawnCollectable(Vector2 Position)
{
	// Get playstate
	PlayState* PS = (PlayState*)Game::GetGame()->GetGameStateMachine()->GetActiveGameState();

	// Check collectable limit
	if ((*PS).m_Collectables.size() >= 10) {
		return;
	}

	// Spawn and set collectable position
	(*PS).m_Collectables.push_back((*PS).AddGameObject<Collectable>());
	(*PS).m_Collectables.back()->SetPosition(Position);
}

Player* PlayState::GetPlayer()
{
	// Get player reference
	PlayState* PS = (PlayState*)Game::GetGame()->GetGameStateMachine()->GetActiveGameState();
	return (*PS).m_SpawnedPlayer;
}

void PlayState::OnStart()
{
	Super::OnStart();

	// Reset score
	m_Score = 0.0f;

	// Add objects
	m_SpawnedPlayer = AddGameObject<Player>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(25);
	m_ScoreText->SetText("Score:0");
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	m_ScoreText->SetFontColor(0, 255, 0, 255);

	// Add to object stacks
	AddObjects();
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Score Text
	std::string ScoreString = "Score:" + 
		std::to_string(static_cast<int>(std::trunc(PlayState::m_Score))
	);

	m_ScoreText->SetText(ScoreString.c_str());

	// Add to object stacks
	AddObjects();
}

void PlayState::OnGarbageCollection()
{
	// Remove destroyed objects from object stacks
	RemoveDestroyedObjects();
}

void PlayState::OnCleanup()
{
	// Destroy collectables
	for (const auto Item : m_Collectables) {
		if (Item != nullptr) {
			Item->DestroyObject();
		}
	}

	// Destroy enemies
	for (const auto Item : m_Enemies) {
		if (Item != nullptr) {
			Item->DestroyObject();
		}
	}

	// Destroy other objects
	m_SpawnedPlayer->DestroyObject();
	m_ScoreText->DestroyObject();

	Super::OnCleanup();
}

void PlayState::AddObjects()
{
	// Add more enemies
	for (int i = m_Enemies.size(); i < 25; i++) {
		m_Enemies.push_back(AddGameObject<Enemy>());
	}
}

void PlayState::RemoveDestroyedObjects()
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
