#pragma once
#include "GameStates/GameState.h"

class TextObject;

class SplashScreenState : public GameState {
public:
	SplashScreenState();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnCleanup() override;

private:
	TextObject* m_TitleText;

	// Timers
	float m_BaseWaitTimer;
	float m_WaitTimer;

	float m_BaseTextTimer;
	float m_TextTimer;

	float m_BaseScreenTimer;
	float m_ScreenTimer;
};