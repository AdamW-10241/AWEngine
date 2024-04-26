#include "GameStates/ControlsInfoState.h"

#include "GameObjects/TextObject.h"

#include "Game.h"
#include "Input.h"

void ControlsInfoState::OnStart()
{
	// Add objects
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/NinjaAdventure/Custom Background/Background_MainMenuState.png");
	m_Background->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		Game::GetGame()->WindowHeightF() / 2.0f }
	);
	m_Background->SetScale(1.0f);

	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	float TitleOffset = HalfHeight / 1.5f;
	m_TitleText = AddGameObject<TextObject>();
	m_TitleText->SetAligment(AL_CENTER);
	m_TitleText->SetPosition(Vector2(HalfWidth, HalfHeight - TitleOffset));
	m_TitleText->SetFontSize(60);
	m_TitleText->SetText("RUINS OF OBLIVION");

	float SubTitleOffset = HalfHeight / 3.0f;
	float BaseOffset = HalfHeight * 1.25f;

	m_InfoText = AddGameObject<TextObject>();
	m_InfoText->SetAligment(AL_CENTER);
	m_InfoText->SetPosition(Vector2(HalfWidth, BaseOffset - SubTitleOffset));
	m_InfoText->SetFontSize(25);
	m_InfoText->SetText("PLACE INFO HERE");

	m_QuitText = AddGameObject<TextObject>();
	m_QuitText->SetAligment(AL_CENTER);
	m_QuitText->SetPosition(Vector2(HalfWidth, BaseOffset + SubTitleOffset));
	m_QuitText->SetFontSize(45);
	m_QuitText->SetText("MENU - M");
}

void ControlsInfoState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_M)) {
		// Make Intro Level
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new MainMenuState);
	}
}

void ControlsInfoState::OnCleanup()
{
	m_TitleText->DestroyObject();
	m_InfoText->DestroyObject();
	m_QuitText->DestroyObject();
}
