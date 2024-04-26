#include "GameStates/MainMenuState.h"

#include "GameObjects/TextObject.h"

#include "Game.h"
#include "Input.h"

void MainMenuState::OnStart()
{
	// Add objects
	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	m_TitleText = AddGameObject<TextObject>();
	m_TitleText->SetAligment(AL_CENTER);
	m_TitleText->SetPosition(Vector2(HalfWidth, HalfHeight));
	m_TitleText->SetFontSize(30);
	m_TitleText->SetText("Press Enter/Return to Start Game");
}

void MainMenuState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_RETURN)) {
		auto NewState = new PlayState();
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(NewState);
	}
}

void MainMenuState::OnCleanup()
{
	m_TitleText->DestroyObject();
}
