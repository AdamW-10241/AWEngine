#pragma once
#include "EngineTypes.h"
#include "GameStates/GameState.h"

#include "GameStates/ControlsInfoState.h"
#include "GameStates/GameOverState.h"
#include "GameStates/MainMenuState.h"
#include "GameStates/PauseState.h"
#include "GameStates/SplashScreenState.h"
#include "GameStates/Levels/PlayState.h"
#include "GameStates/Levels/LevelStateFirst.h"
#include "GameStates/Levels/LevelStateSecond.h"
#include "GameStates/Levels/LevelStateThird.h"

class GameStateMachine {
public:
	GameStateMachine(GameState* DefaultGameState = new GameState());
	~GameStateMachine() = default;

	// Return the current active game state
	GameState* GetActiveGameState() const;

	// Cleanup the game state machine and remove all game states
	void Cleanup();

	// Add or switch a game state
	void SetNewGameState(GameState* NewGameState = new GameState(), bool IsAdditive = false);

	// Collect Garbage at the end of each frame
	void GarbageCollection();
	
	// Run at the start of each frame
	void PreLoop();

	// Detects input of the game
	void ProcessInput(Input* GameInput);

	// Update each frame after input
	void Update(float DeltaTime);

	// Render the game object bounds
	void Render(SDL_Renderer* Renderer);

private:
	// Store all active game states
	TArray<GameState*> m_ActiveGameStateStack;

	// Store all game states ready for spawn on next loop
	TArray<GameState*> m_PendingGameStateStack;
};