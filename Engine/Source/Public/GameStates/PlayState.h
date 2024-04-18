#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Player;

class PlayState : public GameState {
public:
	PlayState();

	// Set max enemies
	void SetMaxEnemies() {
		m_MinEnemyFrequency = 0.05f;
		m_EnemyFrequency = m_MinEnemyFrequency;
	}

	// Toggle alt enemies
	void ToggleAltEnemies() {
		m_AltEnemy = !m_AltEnemy;
	}

public:
	// Reference to the player
	Player* m_PlayerRef;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	void EnemySpawner(float DeltaTime);

	// Text update functions
	void UpdateScore();
	void UpdateLives();
	void UpdateFrequencyText();

protected:
	// Text rendering objects
	TextObject* m_ScoreText;
	TextObject* m_PlayerLivesText;
	TextObject* m_FreqText;
	
	// Player life counter
	int m_PlayerLives;

	// Timer to reset game after death
	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_MinEnemyFrequency, m_MaxEnemyFrequency;
	float m_EnemyFrequency, m_EnemySpawnTimer;

	// Flags for alternate sprites
	bool m_AltEnemy;
};