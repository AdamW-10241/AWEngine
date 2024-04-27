#pragma once
#include "GameStates/GameState.h"

class TextObject;

class PauseState : public GameState {
public:
	PauseState() :
		m_TitleText(nullptr),
		m_PauseText(nullptr),
		m_MenuText(nullptr) {}

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnCleanup() override;

private:
	TextObject* m_TitleText;

	TextObject* m_PauseText;

	TextObject* m_MenuText;
};