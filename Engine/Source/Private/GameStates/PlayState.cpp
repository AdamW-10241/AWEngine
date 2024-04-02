#include "GameStates/PlayState.h"

#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/TextObject.h"
#include <string>
#include "Debug.h"

#define Super GameState

PlayState::PlayState()
{
	m_SpawnedEnemy = nullptr;
	m_SpawnedPlayer = nullptr;
	m_ScoreText = nullptr;
	m_PlayerText = nullptr;
	m_EnemyText = nullptr;
	m_RotateText = nullptr;
	m_HideText = nullptr;
	m_SizeText = nullptr;
}

void PlayState::OnStart()
{
	Super::OnStart();

	m_SpawnedEnemy = AddGameObject<Enemy>();
	m_SpawnedPlayer = AddGameObject<Player>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 10.0f, 10.0f });
	m_ScoreText->SetFontSize(35);
	m_ScoreText->SetText("Score: 0");
	m_ScoreText->SetAligment(AL_TOP_LEFT);
	m_ScoreText->SetFontColor(0, 255, 0, 255);

	m_PlayerText = AddGameObject<TextObject>();
	m_PlayerText->SetPosition(m_SpawnedPlayer->GetTransform().Position);
	m_PlayerText->SetFontSize(60);
	m_PlayerText->SetText("I'm following the player!");
	m_PlayerText->SetAligment(AL_TOP_CENTER);
	m_PlayerText->SetFontColor(100, 150, 200, 255);

	m_EnemyText = AddGameObject<TextObject>();
	m_EnemyText->SetPosition(m_SpawnedEnemy->GetTransform().Position);
	m_EnemyText->SetFontSize(40);
	m_EnemyText->SetText("I'm following the enemy!");
	m_EnemyText->SetAligment(AL_BOTTOM_CENTER);
	m_EnemyText->SetFontColor(255, 255, 0, 255);

	m_RotateText = AddGameObject<TextObject>();
	m_RotateText->SetPosition({ 800.0f, 400.0f });
	m_RotateText->SetFontSize(50);
	m_RotateText->SetText("I'm rotating!");
	m_RotateText->SetAligment(AL_TOP_LEFT);
	m_RotateText->SetFontColor(165, 0, 255, 100);

	m_HideText = AddGameObject<TextObject>();
	m_HideText->SetPosition({ 400.0f, 500.0f });
	m_HideText->SetFontSize(20);
	m_HideText->SetText("I appear when the player collides!");
	m_HideText->SetAligment(AL_CENTER);
	m_HideText->SetFontColor(0, 255, 255, 255);

	m_SizeText = AddGameObject<TextObject>();
	m_SizeText->SetPosition({ 200.0f, 200.0f });
	m_SizeText->SetFontSize(15);
	m_SizeText->SetText("I change size!");
	m_SizeText->SetAligment(AL_CENTER);
	m_SizeText->SetFontColor(255, 165, 0, 255);
}

void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Score Text
	static float Score = 0.0f;
	Score += DeltaTime * 10.0f;

	std::string ScoreString = "Score: " + 
		std::to_string(static_cast<int>(std::trunc(Score))
	);

	m_ScoreText->SetText(ScoreString.c_str());
	
	// Follow Text
	m_PlayerText->SetPosition(m_SpawnedPlayer->GetTransform().Position);

	m_EnemyText->SetPosition(m_SpawnedEnemy->GetTransform().Position);

	// Rotate Text
	static float Rotation = 0.0f;
	Rotation += DeltaTime * 10;
	m_RotateText->SetRotation(Rotation);

	// Hide Text
	m_HideText->SetFontColor(0, 255, 255,
		(m_SpawnedPlayer->GetOverlap() == true) * 254 + 1
	);

	// Size Text
	static float Size = 15.0f;
	Size += DeltaTime * 10;
	Size = (Size > 45) ? 15 : Size;

	m_SizeText->SetFontSize((int)Size);
}
