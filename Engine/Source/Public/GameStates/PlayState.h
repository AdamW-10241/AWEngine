#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Player;

class PlayState : public GameState {
public:
	PlayState();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	void EnemySpawner(float DeltaTime);

	// Get a random float value between 2 floats
	float GetRandomFloatRange(float min = 0.0f, float max = 1.0f) const;

	// Text update functions
	void UpdateScore();
	void UpdateLives();
	void UpdateFrequencyText();

protected:
	TextObject* m_ScoreText;
	TextObject* m_PlayerLivesText;
	TextObject* m_FreqText;

	// Reference to the player
	Player* m_PlayerRef;
	
	int m_PlayerLives;

	float m_EndPlayTimer;

	// Timers for enemy spawning
	float m_EnemyFrequency, m_EnemySpawnTimer;
};