#include "GameObjects/Collectables/LoadTrigger.h"

#include "GameStates/GameStateMachine.h"
#include "Game.h"

LoadTrigger::LoadTrigger(uint32_t NextLevel, float DifficultyScale)
{
	m_ScoreValue = 0.0f;
	
	m_Scale = 50.0f;

	m_NextLevel = NextLevel;

	m_DifficultyScale = DifficultyScale;
}

void LoadTrigger::CollectCollectable()
{
	// Change to next level state
	switch (m_NextLevel) {
	case 1:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateFirst(m_DifficultyScale));
		break;
	case 2:
		//Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateSecond(m_DifficultyScale));
		break;
	case 3:
		//Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateThird(m_DifficultyScale));
		break;
	default:
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateIntro);
		break;
	}
}
