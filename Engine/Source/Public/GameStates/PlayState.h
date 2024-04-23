#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Player;

typedef struct _Mix_Music Mix_Music;

class PlayState : public GameState {
public:
	PlayState();

	// Set max enemies
	void SetMaxEnemies() {
		m_MinEnemyFrequency = 0.05f;
		m_EnemyFrequency = m_MinEnemyFrequency;
	}

public:
	// Reference to the player
	Player* m_PlayerRef;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnCleanup() override;

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

	// Music
	Mix_Music* m_BGM;
	
	// Player life counter
	int m_PlayerLives;

	// Timer to reset game after death
	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_MinEnemyFrequency, m_MaxEnemyFrequency;
	float m_EnemyFrequency, m_EnemySpawnTimer;
};