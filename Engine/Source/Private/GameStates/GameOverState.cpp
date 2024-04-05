#include "GameStates/GameOverState.h"
#include "GameObjects/TextObject.h"
#include "Input.h"
#include "GameStates/GameStateMachine.h"
#include "Game.h"
#include <string>

#include "Debug.h"

#define Super GameState

GameOverState::GameOverState()
{
	m_RestartText = nullptr;
	m_ScoreText = nullptr;
}

void GameOverState::OnStart()
{
	m_RestartText = AddGameObject<TextObject>();
	m_RestartText->SetPosition({ 640.0f, 360.0f });
	m_RestartText->SetFontSize(50);
	m_RestartText->SetText("Press \'R\' to restart.");
	m_RestartText->SetAligment(AL_CENTER);
	m_RestartText->SetFontColor(185, 0, 0, 255);

	// Score Text
	std::string ScoreString = "Score:" +
		std::to_string(static_cast<int>(std::trunc(PlayState::GetScore()))
	);

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 640.0f, 200.0f });
	m_ScoreText->SetFontSize(50);
	m_ScoreText->SetText(ScoreString.c_str());
	m_ScoreText->SetAligment(AL_CENTER);
	m_ScoreText->SetFontColor(255, 255, 255, 255);
}

void GameOverState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_R)) {
		// Change to play state
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new PlayState());

		AW_LOG("GameOverState", "GameState changed to the PlayState");
	}
}

void GameOverState::OnCleanup()
{
	// Destroy objects
	m_RestartText->DestroyObject();
	m_ScoreText->DestroyObject();

	Super::OnCleanup();
}
