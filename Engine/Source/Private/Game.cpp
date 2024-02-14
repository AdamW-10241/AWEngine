#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"


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
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	// DEBUG VARS
	m_TestTexture1 = nullptr;
	m_TestTexture2 = nullptr;
	m_TestTexture3 = nullptr;
	m_TestTexture4 = nullptr;
	m_TestTexture5 = nullptr;
	m_TestTexture6 = nullptr;
	m_TestTexture7 = nullptr;
	m_TestTexture8 = nullptr;
	m_TestTexture9 = nullptr;
	m_TestTexture10 = nullptr;
}

Game::~Game()
{
	printf("Game Destroyed.\n");
}

void Game::Initialise()
{
	// TODO: Run initialisation of dependencies
	// Initialise SDL and end the game if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		// If less than 0, initalisation has failed
		AW_LOG("Game", "SDL failed to init: " << SDL_GetError());
		return;
	}

	Start();
}

void Game::Start()
{
	// TODO: Launch the game window
	// Create a window and check if it failed
	m_WindowRef = SDL_CreateWindow(
		"AWEngine",					// Window Title
		SDL_WINDOWPOS_CENTERED,		// Start X position on the screeen
		SDL_WINDOWPOS_CENTERED,		// Start Y position on the screeen
		1280, 720,					// Window resolution
		0);							// Special window setting flags

	// Check if the window failed
	if (m_WindowRef == nullptr)
	{
		// If nullptr, window creation has failed
		AW_LOG("Game", "SDL Window failed to create: " << SDL_GetError());
		// Deallocate used memory
		Cleanup();
		return;
	}

	// Create renderer and check if it failed
	m_RendererRef = SDL_CreateRenderer(m_WindowRef, -1, 0);

	if (m_RendererRef == nullptr)
	{
		// If nullptr, renderer creation has failed
		AW_LOG("Game", "SDL Renderer failed to create: " << SDL_GetError());
		// Deallocate used memory
		Cleanup();
		return;
	}

	// DEBUG
	m_TestTexture1 = new Texture(m_RendererRef);
	if (!m_TestTexture1->ImportTexture("Content/Letters/HRed.png"))
	{
		m_TestTexture1->Cleanup();
		delete m_TestTexture1;
		m_TestTexture1 = nullptr;
	}
	else
	{
		m_TestTexture1->m_PosX = 100.0f;
		m_TestTexture1->m_PosY = 120.0f;
		m_TestTexture1->m_Scale = 1.5f;
	}

	m_TestTexture2 = new Texture(m_RendererRef);
	if (!m_TestTexture2->ImportTexture("Content/Letters/E.png"))
	{
		m_TestTexture2->Cleanup();
		delete m_TestTexture2;
		m_TestTexture2 = nullptr;
	}
	else
	{
		m_TestTexture2->m_PosX = 250.0f;
		m_TestTexture2->m_PosY = 100.0f;
		m_TestTexture2->m_Scale = 1.2f;
	}

	m_TestTexture3 = new Texture(m_RendererRef);
	if (!m_TestTexture3->ImportTexture("Content/Letters/LBlue.png"))
	{
		m_TestTexture3->Cleanup();
		delete m_TestTexture3;
		m_TestTexture3 = nullptr;
	}
	else
	{
		m_TestTexture3->m_PosX = 350.0f;
		m_TestTexture3->m_PosY = 180.0f;
		m_TestTexture3->m_Scale = 1.6f;
	}

	m_TestTexture4 = new Texture(m_RendererRef);
	if (!m_TestTexture4->ImportTexture("Content/Letters/L.png"))
	{
		m_TestTexture4->Cleanup();
		delete m_TestTexture4;
		m_TestTexture4 = nullptr;
	}
	else
	{
		m_TestTexture4->m_PosX = 450.0f;
		m_TestTexture4->m_PosY = 160.0f;
		m_TestTexture4->m_Scale = 1.8f;
	}

	m_TestTexture5 = new Texture(m_RendererRef);
	if (!m_TestTexture5->ImportTexture("Content/Letters/ORed.png"))
	{
		m_TestTexture5->Cleanup();
		delete m_TestTexture5;
		m_TestTexture5 = nullptr;
	}
	else
	{
		m_TestTexture5->m_PosX = 600.0f;
		m_TestTexture5->m_PosY = 130.0f;
		m_TestTexture5->m_Scale = 2.0f;
	}

	m_TestTexture6 = new Texture(m_RendererRef);
	if (!m_TestTexture6->ImportTexture("Content/Letters/WBlue.png"))
	{
		m_TestTexture6->Cleanup();
		delete m_TestTexture6;
		m_TestTexture6 = nullptr;
	}
	else
	{
		m_TestTexture6->m_PosX = 250.0f;
		m_TestTexture6->m_PosY = 450.0f;
		m_TestTexture6->m_Scale = 2.0f;
	}

	m_TestTexture7 = new Texture(m_RendererRef);
	if (!m_TestTexture7->ImportTexture("Content/Letters/O.png"))
	{
		m_TestTexture7->Cleanup();
		delete m_TestTexture7;
		m_TestTexture7 = nullptr;
	}
	else
	{
		m_TestTexture7->m_PosX = 400.0f;
		m_TestTexture7->m_PosY = 470.0f;
		m_TestTexture7->m_Scale = 1.1f;
	}

	m_TestTexture8 = new Texture(m_RendererRef);
	if (!m_TestTexture8->ImportTexture("Content/Letters/RRed.png"))
	{
		m_TestTexture8->Cleanup();
		delete m_TestTexture8;
		m_TestTexture8 = nullptr;
	}
	else
	{
		m_TestTexture8->m_PosX = 550.0f;
		m_TestTexture8->m_PosY = 450.0f;
		m_TestTexture8->m_Scale = 1.8f;
	}

	m_TestTexture9 = new Texture(m_RendererRef);
	if (!m_TestTexture9->ImportTexture("Content/Letters/L.png"))
	{
		m_TestTexture9->Cleanup();
		delete m_TestTexture9;
		m_TestTexture9 = nullptr;
	}
	else
	{
		m_TestTexture9->m_PosX = 720.0f;
		m_TestTexture9->m_PosY = 399.0f;
		m_TestTexture9->m_Scale = 1.7f;
	}

	m_TestTexture10 = new Texture(m_RendererRef);
	if (!m_TestTexture10->ImportTexture("Content/Letters/DBlue.png"))
	{
		m_TestTexture10->Cleanup();
		delete m_TestTexture10;
		m_TestTexture10 = nullptr;
	}
	else
	{
		m_TestTexture10->m_PosX = 870.0f;
		m_TestTexture10->m_PosY = 430.0f;
		m_TestTexture10->m_Scale = 1.5f;
	}

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
	if (m_TestTexture1 != nullptr)
	{
		m_TestTexture1->Cleanup();
		delete m_TestTexture1;
	}
	if (m_TestTexture2 != nullptr)
	{
		m_TestTexture2->Cleanup();
		delete m_TestTexture2;
	}
	if (m_TestTexture3 != nullptr)
	{
		m_TestTexture3->Cleanup();
		delete m_TestTexture3;
	}
	if (m_TestTexture4 != nullptr)
	{
		m_TestTexture4->Cleanup();
		delete m_TestTexture4;
	}
	if (m_TestTexture5 != nullptr)
	{
		m_TestTexture5->Cleanup();
		delete m_TestTexture5;
	}
	if (m_TestTexture6 != nullptr)
	{
		m_TestTexture6->Cleanup();
		delete m_TestTexture6;
	}
	if (m_TestTexture7 != nullptr)
	{
		m_TestTexture7->Cleanup();
		delete m_TestTexture7;
	}
	if (m_TestTexture8 != nullptr)
	{
		m_TestTexture8->Cleanup();
		delete m_TestTexture8;
	}
	if (m_TestTexture9 != nullptr)
	{
		m_TestTexture9->Cleanup();
		delete m_TestTexture9;
	}
	if (m_TestTexture10 != nullptr)
	{
		m_TestTexture10->Cleanup();
		delete m_TestTexture10;
	}
	
	// Cleanup SDL
	if (m_RendererRef != nullptr)
	{
		// Deallocate the renderer if it exists
		SDL_DestroyRenderer(m_RendererRef);
	}

	if (m_WindowRef != nullptr)
	{
		// Deallocates the window if it exists
		SDL_DestroyWindow(m_WindowRef);
	}

	SDL_Quit();

	AW_LOG("Game", "Game has deallocated all memory.");
}

void Game::ProcessInput()
{
	// Data type that reads SDL window input events
	SDL_Event InputEvent;

	// Run through each input each frame
	while (SDL_PollEvent(&InputEvent))
	{
		// If the window cross is pressed, close the app
		if (InputEvent.type == SDL_QUIT)
		{
			QuitApp();
		}
	}
}

void Game::Update()
{
	// TODO: Update Game Logic
	static float Angle = 0.0f;
	if (m_TestTexture1 != nullptr)
	{
		m_TestTexture1->m_Angle = Angle;
	}
	if (m_TestTexture8 != nullptr)
	{
		m_TestTexture8->m_Angle = Angle / 2;
	}
	Angle += 0.025f;
}

void Game::Render()
{
	// Tell the renderer the color used next
	SDL_SetRenderDrawColor(m_RendererRef, 50, 50, 80, 255);
	// Used the color to clear the previous frame
	SDL_RenderClear(m_RendererRef);

	// TODO: Render custom graphics
	if (m_TestTexture1 != nullptr)
	{
		m_TestTexture1->Draw();
	}
	if (m_TestTexture2 != nullptr)
	{
		m_TestTexture2->Draw();
	}
	if (m_TestTexture3 != nullptr)
	{
		m_TestTexture3->Draw();
	}
	if (m_TestTexture4 != nullptr)
	{
		m_TestTexture4->Draw();
	}
	if (m_TestTexture5 != nullptr)
	{
		m_TestTexture5->Draw();
	}
	if (m_TestTexture6 != nullptr)
	{
		m_TestTexture6->Draw();
	}
	if (m_TestTexture7 != nullptr)
	{
		m_TestTexture7->Draw();
	}
	if (m_TestTexture8 != nullptr)
	{
		m_TestTexture8->Draw();
	}
	if (m_TestTexture9 != nullptr)
	{
		m_TestTexture9->Draw();
	}
	if (m_TestTexture10 != nullptr)
	{
		m_TestTexture10->Draw();
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	// TODO: Delete Objects at the end of each frame.
}
