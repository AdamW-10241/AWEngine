#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Enemy;
class Player;
class Collectable;
class Vector2;

class PlayState : public GameState {
public:
	PlayState();

	// Add to the game score
	static void AddScore(float Score) { m_Score += Score; }

	// Spawn a collectable into the level
	static void SpawnCollectable(Vector2 Position);

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnGarbageCollection() override;

	virtual void OnCleanup() override;

	virtual void AddObjects();

	virtual void RemoveDestroyedObjects();

protected:
	Player* m_SpawnedPlayer;

	TextObject* m_ScoreText;

private:
	static float m_Score;

	// Store spawned collectables
	TArray<Collectable*> m_Collectables;

	// Store spawned enemies
	TArray<Enemy*> m_Enemies;
};