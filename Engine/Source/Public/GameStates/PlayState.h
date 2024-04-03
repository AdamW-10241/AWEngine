#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Enemy;
class Player;
class Collectable;

class PlayState : public GameState {
public:
	PlayState();

	// Add to the game score
	static void AddScore(float Score) { m_Score += Score; }

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnGarbageCollection() override;

	virtual void OnCleanup() override;

protected:
	Player* m_SpawnedPlayer;
	TextObject* m_ScoreText;

private:
	static float m_Score;

	// Store spawned collectables
	TArray<Collectable*> m_Collectables;
	TArray<Enemy*> m_Enemies;
};