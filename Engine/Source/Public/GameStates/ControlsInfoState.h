#pragma once
#include "GameStates/GameState.h"

class TextObject;

class ControlsInfoState : public GameState {
public:
	ControlsInfoState() :
		m_TitleText(nullptr),
		m_InfoText(nullptr),
		m_QuitText(nullptr) {}

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnCleanup() override;

private:
	TextObject* m_TitleText;

	TextObject* m_InfoText;

	TextObject* m_QuitText;
};
