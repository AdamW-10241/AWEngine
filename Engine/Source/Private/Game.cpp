#include "Game.h"
#include <iostream>

Game* Game::GetGame()
{
	// Create a Game Singleton
	// static - only run initialisation once
	// this line will only run once: thread safe
	static Game* GameSingleton = new Game();
	
	return GameSingleton;
}

void Game::DestroyGame()
{
	delete GetGame();
}

Game::Game()
{
	printf("Game Created.\n");

	// Initalise Member Variabless
	m_IsGameOpen = true;
}

Game::~Game()
{
	printf("Game Destroyed.\n");
}

void Game::Initialise()
{
	printf("Initialise Game.\n");

	// TODO: Run initialisation of dependencies

	Start();
}

void Game::Start()
{
	printf("Start Game.\n");

	// TODO: Launch the game window

	GameLoop();
}

void Game::GameLoop()
{
	// while IsGameOpen is true, keep the game running
	while (m_IsGameOpen)
	{
		ProcessInput();
		Update();
		Render();
		CollectGarbage();
	}

	Cleanup();
}

void Game::Cleanup()
{
	printf("Cleanup Game.\n");
}

void Game::ProcessInput()
{
	printf("Process Input.\n");
}

void Game::Update()
{
	printf("Update Game Logic.\n");

	static int Frames = 0;

	if (Frames >= 30)
	{
		m_IsGameOpen = false;
	}
	else
	{
		++Frames;
	}
}

void Game::Render()
{
	printf("Render Graphics.\n");
}

void Game::CollectGarbage()
{
	printf("Collect Garbage.\n");
}
