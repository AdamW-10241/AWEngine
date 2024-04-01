#pragma once
#include "GameStates/GameState.h"

class TextObject;

class PlayState : public GameState {
public:
	PlayState() = default;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	TextObject* m_ScoreText;
};