#include "GameStates/PlayState.h"

#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include <string>

#define Super GameState

PlayState::PlayState()
{
	m_SpawnedEnemy = nullptr;
	m_ScoreText = nullptr;
	m_Text1 = nullptr;
	m_Text2 = nullptr;
	m_Text3 = nullptr;
}

void PlayState::OnStart()
{
	Super::OnStart();

	m_SpawnedEnemy = AddGameObject<Enemy>();
	AddGameObject<Player>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetText("Score: 0");
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	m_ScoreText->SetFontColor(255, 0, 0, 255);

	m_Text1 = AddGameObject<TextObject>();
	m_Text1->SetPosition({ 400.0f, 400.0f });
	m_Text1->SetFontSize(60);
	m_Text1->SetText("This is some text!");
	m_Text1->SetAligment(AL_TOP_LEFT);
	m_Text1->SetFontColor(255, 0, 0, 255);

	m_Text2 = AddGameObject<TextObject>();
	m_Text2->SetPosition(m_SpawnedEnemy->GetTransform().Position);
	m_Text2->SetFontSize(40);
	m_Text2->SetText("I'm following the enemy!");
	m_Text2->SetAligment(AL_CENTER);
	m_Text2->SetFontColor(0, 255, 0, 100);

	m_Text3 = AddGameObject<TextObject>();
	m_Text3->SetPosition({ 400.0f, 400.0f });
	m_Text3->SetFontSize(60);
	m_Text3->SetText("I'm rotating!");
	m_Text3->SetAligment(AL_TOP_LEFT);
	m_Text3->SetFontColor(255, 0, 0, 255);
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

	m_Text2->SetPosition(m_SpawnedEnemy->GetTransform().Position);
}
