#pragma once
#include "GameStates/GameState.h"

class TextObject;

class MainMenuState : public GameState {
public:
	MainMenuState() : 
		m_TitleText(nullptr),
		m_StartText(nullptr),
		m_InfoText(nullptr),
		m_QuitText(nullptr) {}

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnCleanup() override;

private:
	TextObject* m_TitleText;

	TextObject* m_StartText;

	TextObject* m_InfoText;

	TextObject* m_QuitText;
};