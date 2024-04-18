#include "GameStates/MainMenuState.h"

#include "Game.h"
#include "Input.h"
#include "GameObjects/TextObject.h"
#include "GameObjects/Background.h"

void MainMenuState::OnStart()
{
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/Background/Starfields/Starfield_07-1024x1024.png");
	m_Background->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		Game::GetGame()->WindowHeightF() / 2.0f }
	);
	m_Background->SetScale({ 1.5f, 1.0f });
	
	m_TitleText = AddGameObject<TextObject>();
	m_TitleText->SetAligment(AL_CENTER);

	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	m_TitleText->SetPosition(Vector2(HalfWidth, HalfHeight));
	m_TitleText->SetFontSize(40);

	m_TitleText->SetText("Press Enter/Return to Start Game");
}

void MainMenuState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_RETURN)) {
		auto NewState = new PlayState();
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(NewState);
	}
}
