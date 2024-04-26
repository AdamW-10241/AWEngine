#pragma once
#include "GameStates/GameState.h"

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

	void EnemySpawner(float DeltaTime);

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

	void UpdateFrequencyText();

protected:
	// Text rendering objects
	TextObject* m_ScoreText;

	TextObject* m_PlayerHealthText;

	TextObject* m_FreqText;
	
	// Player health counter
	float m_PlayerHealth;

	// Timer to reset game after death
	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_EnemyFrequency, m_EnemySpawnTimer;
};