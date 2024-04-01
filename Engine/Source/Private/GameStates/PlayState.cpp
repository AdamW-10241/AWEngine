#include "GameStates/PlayState.h"

#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include <string>

#define Super GameState

void PlayState::OnStart()
{
	Super::OnStart();

	AddGameObject<Enemy>();
	AddGameObject<Player>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(40);
	m_ScoreText->SetText("Score: 0");
	m_ScoreText->SetAligment(AL_TOP_LEFT);
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	static float Score = 0.0f;
	Score += DeltaTime * 10.0f;

	std::string ScoreString = "Score: " + 
		std::to_string(static_cast<int>(std::trunc(Score))
	);

	m_ScoreText->SetText(ScoreString.c_str());
}
