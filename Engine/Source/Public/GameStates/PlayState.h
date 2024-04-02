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

protected:
	Enemy* m_SpawnedEnemy;
	Player* m_SpawnedPlayer;
	TextObject* m_ScoreText;
};