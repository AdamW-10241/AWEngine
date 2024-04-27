#pragma once
#include "GameStates/GameState.h"

#include "GameObjects/Collectables/LoadTrigger.h"

class TextObject;
class Player;

class PlayState : public GameState {
public:
	PlayState();

public:
	// Reference to the player
	Player* m_PlayerRef;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnCleanup() override;

	// Add objects
	void AddBackground(Vector2 Position, float Scale, const char* PathToFile);

	void AddPlayer(Vector2 Position, float Scale);

	//template<class T, std::enable_if_t<std::is_base_of_v<PlayState, T>, T>* = nullptr>
	//void AddLoadTrigger(Vector2 Position) {
	//	// Add trigger
	//	const auto Trigger = AddGameObject<LoadTrigger>(new T*);
	//	Trigger->SetPosition(Position);
	//}

	void EnemySpawner(float DeltaTime, float Scale);

	// Check player dead (to end game)
	// Must be used with UpdateHealth() to update the stored player health
	void CheckEndGame(float DeltaTime);

	// Reset score
	void ResetScore();

	// HUD
	void CreateHUD();

	void UpdateHUD();

	// Text update functions
	void UpdateScore();

	void UpdateHealth();

protected:
	// Text rendering objects
	TextObject* m_ScoreText;

	TextObject* m_PlayerHealthText;
	
	// Player health counter
	float m_PlayerHealth;

	// Timer to reset game after death
	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_EnemyFrequency, m_EnemySpawnTimer;
};