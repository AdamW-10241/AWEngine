#include "GameStates/MainMenuState.h"

#include "GameObjects/TextObject.h"

#include "Game.h"
#include "Input.h"

void MainMenuState::OnStart()
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

	m_StartText = AddGameObject<TextObject>();
	m_StartText->SetAligment(AL_CENTER);
	m_StartText->SetPosition(Vector2(HalfWidth, BaseOffset - SubTitleOffset));
	m_StartText->SetFontSize(45);
	m_StartText->SetText("START - S");

	m_InfoText = AddGameObject<TextObject>();
	m_InfoText->SetAligment(AL_CENTER);
	m_InfoText->SetPosition(Vector2(HalfWidth, BaseOffset));
	m_InfoText->SetFontSize(45);
	m_InfoText->SetText("INFORMATION - I");

	m_QuitText = AddGameObject<TextObject>();
	m_QuitText->SetAligment(AL_CENTER);
	m_QuitText->SetPosition(Vector2(HalfWidth, BaseOffset + SubTitleOffset));
	m_QuitText->SetFontSize(45);
	m_QuitText->SetText("QUIT - Q");
}

void MainMenuState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_S)) {
		if (m_PauseTimer <= 0.0f) {
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateIntro);
		}
	}

	if (GameInput->IsKeyDown(AW_KEY_I)) {
		if (m_PauseTimer <= 0.0f) {
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(new ControlsInfoState);
		}
	}

	if (GameInput->IsKeyDown(AW_KEY_Q)) {
		Game::GetGame()->QuitApp();
	}
}

void MainMenuState::OnCleanup()
{
	m_TitleText->DestroyObject();
	m_StartText->DestroyObject();
	m_InfoText->DestroyObject();
	m_QuitText->DestroyObject();
}
