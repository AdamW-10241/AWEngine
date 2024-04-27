#include "GameObjects/Collectables/LoadTrigger.h"
#include "GameStates/GameStateMachine.h"

LoadTrigger::LoadTrigger()
{
	m_ScoreValue = 0.0f;
	
	m_Scale = 50.0f;

	//m_NextLevel = NextLevel;
}

void LoadTrigger::CollectCollectable()
{
	// Change to next level state
	Game::GetGame()->GetGameStateMachine()->SetNewGameState(new LevelStateFirst);
}
