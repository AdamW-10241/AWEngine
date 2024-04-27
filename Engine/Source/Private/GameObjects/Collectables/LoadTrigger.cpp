#include "GameObjects/Collectables/LoadTrigger.h"

#include "GameStates/GameStateMachine.h"
#include "Game.h"

#define Super Collectable

LoadTrigger::LoadTrigger(uint32_t NextLevel, float DifficultyScale, float Scale)
{
	m_ScoreValue = 0.0f;
	
	m_Scale = Scale;
	m_Size = 64.0f;

	m_NextLevel = NextLevel;

	m_DifficultyScale = DifficultyScale;

	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/CustomLock.png"
	);

	m_Active = false;
	m_MainSprite->SetActive(!m_Active);
}

void LoadTrigger::SetActive()
{
	m_Active = true;
	m_Bounds->m_Active = m_Active;
	m_MainSprite->SetActive(!m_Active);
}

void LoadTrigger::OnStart()
{
	Super::OnStart();

	m_Bounds->m_Active = m_Active;
}

void LoadTrigger::CollectCollectable()
{
	if (!m_Active) {
		return;
	}
	
	// Change to next level state
	switch (m_NextLevel) {
	case 1:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateFirst(m_DifficultyScale));
		break;
	case 2:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateSecond(m_DifficultyScale));
		break;
	case 3:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateThird(m_DifficultyScale));
		break;
	default:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateIntro);
		break;
	}
}
