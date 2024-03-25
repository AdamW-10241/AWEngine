#include "GameStates/PlayState.h"

#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "Input.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

void PlayState::OnStart()
{
	AddGameObject<Enemy>();
	AddGameObject<Player>();
}

void PlayState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_1)) {
		GameState* NewState = new PlayState();
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(NewState);
	}
}
