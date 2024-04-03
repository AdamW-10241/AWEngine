#pragma once
#include "GameStates/GameState.h"

class TextObject;
class Input;

class GameOverState : public GameState {
public:
	GameOverState();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnCleanup() override;

protected:
	TextObject* m_RestartText;
};