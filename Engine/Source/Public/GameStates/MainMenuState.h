#pragma once
#include "GameStates/GameState.h"

class TextObject;

class MainMenuState : public GameState {
public:
	MainMenuState() : m_TitleText(nullptr) {}

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnCleanup() override;

private:
	TextObject* m_TitleText;
};