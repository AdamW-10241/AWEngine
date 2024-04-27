#include "GameStates/SplashScreenState.h"

#include "GameObjects/TextObject.h"

#include "Game.h"
#include "Input.h"
#include <cmath>

SplashScreenState::SplashScreenState()
{
	m_TitleText = nullptr;
	m_BaseWaitTimer = 2.0f;
	m_WaitTimer = m_BaseWaitTimer;
	m_BaseTextTimer = 3.5f;
	m_TextTimer = m_BaseTextTimer;
	m_BaseScreenTimer = 0.5f;
	m_ScreenTimer = m_BaseScreenTimer;
}

void SplashScreenState::OnStart()
{
	LoadMusic("Content/Audio/MUSIC_Splash.wav");
	
	// Add objects
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/NinjaAdventure/Custom Background/Background_GameOverState.png");
	m_Background->SetPosition({ 640.0f, 360.0f });
	m_Background->SetScale(1.1f);
	
	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	m_TitleText = AddGameObject<TextObject>();
	m_TitleText->SetAligment(AL_CENTER);
	m_TitleText->SetPosition(Vector2(HalfWidth, HalfHeight));
	m_TitleText->SetFontSize(65);
	m_TitleText->SetText("RUINS OF OBLIVION");
}

void SplashScreenState::OnUpdate(float DeltaTime)
{
	// Decrease timer
	if (m_WaitTimer > 0.0f) {
		m_WaitTimer -= DeltaTime;
		return;
	}

	if (m_TextTimer > 0.0f) {
		m_TextTimer -= DeltaTime;
		
		int Alpha = std::max((int)(255 * (m_TextTimer / m_BaseTextTimer)), 1);
		m_TitleText->SetFontColor(255, 255, 255, Alpha);
		return;
	}

	if (m_ScreenTimer > 0.0f) {
		m_ScreenTimer -= DeltaTime;
		return;
	}

	// Change to menu state
	Game::GetGame()->GetGameStateMachine()->SetNewGameState(new MainMenuState());
}

void SplashScreenState::OnCleanup()
{
	m_TitleText->DestroyObject();
}
