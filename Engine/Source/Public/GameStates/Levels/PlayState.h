#pragma once
#include "GameStates/GameState.h"

#include "GameObjects/Collectables/LoadTrigger.h"
#include "GameObjects/HUD.h"

class Player;

class PlayState : public GameState {
public:
	PlayState();

	// Mark killed enemy
	void EnemyKilled() { m_EnemiesKilled++; }

	// Set key collected
	void SetKeyCollected() { m_KeyCollected = true; }

	// Get HUD
	HUD* GetHUD() const { return m_HUD; }

public:
	// Reference to the player
	Player* m_PlayerRef;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnCleanup() override;

	virtual void OnPause() { m_HUD->SetVisibleText(false); }

	// Add objects
	void AddBackground(Vector2 Position, float Scale, const char* PathToFile);

	void AddPlayer(Vector2 Position, float Scale);

	void EnemySpawner(float DeltaTime, float Scale);

	void AddKey(Vector2 Position);

	void AddLoadTrigger();

	// Check if player is dead to end game
	void CheckEndGame(float DeltaTime);

	void CheckKeySpawn();

	void CheckTriggerSpawn();

	// Scale difficulty
	void ScaleDifficulty();

	// Reset score
	void ResetScore();

	// HUD
	void CreateHUD();

protected:
	// Text rendering objects
	HUD* m_HUD;

	// Timer to reset game after death
	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_EnemyFrequency, m_EnemySpawnTimer;

	// Enemy
	Vector2 m_EnemySpawnPositions[4];

	float m_DifficultyScale;

	float m_DifficultyScaleIncreaseAmount;

	// Key
	int m_EnemiesKilled;

	int m_KeyRequirement;

	bool m_KeySpawned;

	Vector2 m_KeySpawnPosition;

	bool m_KeyCollected;

	// Next level value
	int m_NextLevelValue;

	// Load trigger
	LoadTrigger* m_LoadTrigger;

	Vector2 m_LoadTriggerPosition;

	float m_LoadTriggerScale;

	bool m_TriggerActive;
};