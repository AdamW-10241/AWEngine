#pragma once
#include "GameStates/GameState.h"

#include "GameObjects/Collectables/LoadTrigger.h"

class TextObject;
class Player;

class PlayState : public GameState {
public:
	PlayState();

	// Mark killed enemy
	void EnemyKilled() { m_EnemiesKilled++; }

	// Set key collected
	void SetKeyCollected() { m_KeyCollected = true; }

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

	void EnemySpawner(float DeltaTime, float Scale);

	void AddKey(Vector2 Position);

	void AddLoadTrigger(Vector2 Position);

	// Check player dead (to end game)
	// Must be used with UpdateHealth() to update the stored player health
	void CheckEndGame(float DeltaTime);

	void CheckKeySpawn();

	void CheckTriggerSpawn();

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
	Vector2 m_LoadTriggerPosition;

	bool m_TriggerSpawned;
};