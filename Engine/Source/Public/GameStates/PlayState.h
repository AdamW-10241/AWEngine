#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Enemy;

class PlayState : public GameState {
public:
	PlayState();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	Enemy* m_SpawnedEnemy;
	TextObject* m_ScoreText;
	TextObject* m_Text1;
	TextObject* m_Text2;
	TextObject* m_Text3;
};