#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Enemy;
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
	void UpdateFrequencyText();

protected:
	TextObject* m_ScoreText;
	TextObject* m_FreqText;

	// Timers for enemy spawning
	float m_EnemyFrequency, m_EnemySpawnTimer;
};