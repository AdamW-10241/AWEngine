#include "GameStates/GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState* DefaultGameState)
{
	SetNewGameState(DefaultGameState);
}

GameState* GameStateMachine::GetActiveGameState() const
{
	return m_ActiveGameStateStack.back();
}

void GameStateMachine::Cleanup()
{
	// Delete all pending game states
	for (const auto GS : m_PendingGameStateStack) {
		GS->Cleanup();
		delete GS;
	}

	for (const auto GS : m_ActiveGameStateStack) {
		GS->Cleanup();
		delete GS;
	}
}

void GameStateMachine::SetNewGameState(GameState* NewGameState, bool IsAdditive)
{
	if (IsAdditive) {
		return;
	}

	// Clear all of the current game states
	for (const auto GS : m_ActiveGameStateStack) {
		GS->DestroyGameState();
	}

	if (NewGameState != nullptr) {
		// Adding it to be spawned on the next loop
		m_PendingGameStateStack.push_back(NewGameState);
	}
}

void GameStateMachine::GarbageCollection()
{
	GetActiveGameState()->GarbageCollection();
	
	if (m_ActiveGameStateStack.size() < 2) {
		return;
	}
	
	std::erase_if(m_ActiveGameStateStack,
		[](GameState* GS) {
			if (!GS->IsPendingDestroy()) {
				return false;
			}

			GS->Cleanup();
			delete GS;

			return true; }
	);
}

void GameStateMachine::PreLoop()
{
	for (const auto GS : m_PendingGameStateStack) {
		m_ActiveGameStateStack.push_back(GS);
		GS->Start();
	}

	m_PendingGameStateStack.clear();

	GetActiveGameState()->PreLoop();
}

void GameStateMachine::ProcessInput(Input* GameInput)
{
	GetActiveGameState()->ProcessInput(GameInput);
}

void GameStateMachine::Update(float DeltaTime)
{
	GetActiveGameState()->Update(DeltaTime);
}

void GameStateMachine::Render(SDL_Renderer* Renderer)
{
	GetActiveGameState()->Render(Renderer);
}
