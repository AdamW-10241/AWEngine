#include "GameStates/PauseState.h"

#include "GameObjects/TextObject.h"
#include "GameObjects/HUD.h"

#include "Game.h"
#include "Input.h"

#define Super GameState

void PauseState::OnStart()
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

	m_PauseText = AddGameObject<TextObject>();
	m_PauseText->SetAligment(AL_CENTER);
	m_PauseText->SetPosition(Vector2(HalfWidth, BaseOffset - SubTitleOffset));
	m_PauseText->SetFontSize(45);
	m_PauseText->SetText("PAUSED - P");

	m_MenuText = AddGameObject<TextObject>();
	m_MenuText->SetAligment(AL_CENTER);
	m_MenuText->SetPosition(Vector2(HalfWidth, BaseOffset + SubTitleOffset));
	m_MenuText->SetFontSize(45);
	m_MenuText->SetText("MENU - M");
}

void PauseState::OnProcessInput(Input* GameInput)
{	
	if (GameInput->IsKeyDown(AW_KEY_M)) {
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new MainMenuState);
		return;
	}

	if (GameInput->IsKeyDown(AW_KEY_P)) {
		if (m_PauseTimer <= 0.0f) {
			if (const auto PS = dynamic_cast<PlayState*>(Game::GetGame()->GetGameStateMachine()->GetInactiveGameState())) {
				PS->GetHUD()->SetVisibleText(true);
			}
			
			DestroyGameState();
			return;
		}
	}
}

void PauseState::OnCleanup()
{
	m_TitleText->DestroyObject();
	m_PauseText->DestroyObject();
	m_MenuText->DestroyObject();
}