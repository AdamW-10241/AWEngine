#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Background;
class Enemy;
class Player;
class Collectable;
struct Vector2;

class PlayState : public GameState {
public:
	PlayState();

	// Add to the game score
	static void AddScore(float Score) { m_Score += Score; }

	// Get the game score
	static float const GetScore() { return m_Score; }

	// Spawn a collectable into the level
	static void SpawnCollectable(Vector2 Position);

	// Get a reference to the player
	static Player* GetPlayer();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnGarbageCollection() override;

	virtual void OnCleanup() override;

	virtual void AddStackObjects();

	virtual void RemoveDestroyedObjects();

protected:
	// Global score
	static float m_Score;
	
	// Store player
	Player* m_SpawnedPlayer;

	// Store score text
	TextObject* m_ScoreText;

	// Store spawned collectables
	TArray<Collectable*> m_Collectables;

	// Store spawned enemies
	TArray<Enemy*> m_Enemies;
};