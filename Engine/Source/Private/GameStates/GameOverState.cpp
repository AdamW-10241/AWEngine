#include "GameStates/GameOverState.h"
#include "GameObjects/TextObject.h"
#include "Input.h"
#include "GameStates/GameStateMachine.h"
#include "Game.h"
#include <string>
#include "GameObjects/Background.h"

#include "Debug.h"

#define Super GameState

GameOverState::GameOverState()
{
	m_RestartText = nullptr;
	m_ScoreText = nullptr;
	m_HintText = nullptr;
}

void GameOverState::OnStart()
{
	// Add objects
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/NinjaAdventure/Custom Background/Background_GameOverState.png");
	m_Background->SetPosition({ 640.0f, 360.0f });
	m_Background->SetScale(0.9f);

	m_RestartText = AddGameObject<TextObject>();
	m_RestartText->SetPosition({ 640.0f, 500.0f });
	m_RestartText->SetFontSize(50);
	m_RestartText->SetText("Press \'R\' to restart.");
	m_RestartText->SetAligment(AL_CENTER);
	m_RestartText->SetFontColor(240, 0, 0, 255);

	// Score text
	std::string ScoreString = "Score:" +
		std::to_string(static_cast<int>(std::trunc(PlayState::GetScore()))
	);

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 640.0f, 200.0f });
	m_ScoreText->SetFontSize(50);
	m_ScoreText->SetText(ScoreString.c_str());
	m_ScoreText->SetAligment(AL_CENTER);
	m_ScoreText->SetFontColor(255, 255, 255, 255);

	m_HintText = AddGameObject<TextObject>();
	m_HintText->SetPosition({ 640.0f, 350.0f });
	m_HintText->SetFontSize(20);
	m_HintText->SetText("Move with WASD and Fire Toward Cursor with LEFT-CLICK!");
	m_HintText->SetAligment(AL_CENTER);
	m_HintText->SetFontColor(255, 255, 255, 255);
}

void GameOverState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_R)) {
		// Change to play state
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new PlayState());

		AW_LOG("GameOverState", "GameState changed to the PlayState");
	}
}
