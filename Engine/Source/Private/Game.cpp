#include "Game.h"
#include "SDL2/SDL.h"
#include "Graphics/Texture.h"
#include "Input.h"
#include "GameObjects/GameObject.h"
#include "GameStates/GameStateMachine.h"
#include "SDL2/SDL_ttf.h"
#include "Graphics/Text.h"

#include "Debug.h"

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

Texture* Game::ImportTexture(const char* PathToFile)
{
	Texture* NewTexture = new Texture(m_RendererRef);

	// Loop through all of the game textures 
	for (Texture* TexRef : m_TextureStack)
	{
		// Check if the texture has already been imported
		if (std::strcmp(TexRef->GetPath(), PathToFile) == 0)
		{
			// If there was a matching path
			// Copy the successfully mathced element
			NewTexture->CopyTexture(TexRef);
			// Add it to the texture stack
			m_TextureStack.push_back(NewTexture);
			// Return the new texture and ignore the rest of the function
			return NewTexture;
		}
	}

	// Attempt to import the texture
	if (!NewTexture->ImportTexture(PathToFile))
	{
		// If it failed, delete and update new texture to nullptr
		delete NewTexture;
		NewTexture = nullptr;
	}
	else
	{
		// If the import was successful
		m_TextureStack.push_back(NewTexture);
	}

	return NewTexture;
}

void Game::DestroyTexture(Texture* TextureToDestroy)
{
	int TexturesFound = 0;

	// Loop through all of the textures
	for (Texture* TexRef : m_TextureStack)
	{
		// If the texture has a matching path
		if (std::strcmp(TextureToDestroy->GetPath(), TexRef->GetPath()) == 0)
		{
			++TexturesFound;

			if (TexturesFound > 1)
			{
				break;
			}
		}
	}

	// If there is not a copy deallocate all memory related to the texture
	if (TexturesFound <= 1)
	{
		TextureToDestroy->Cleanup();
	}

	// Find the texture in the array
	auto it = std::find(m_TextureStack.begin(), m_TextureStack.end(), TextureToDestroy);
	// If the texture is found
	if (it != m_TextureStack.end())
	{
		m_TextureStack.erase(it);
	}

	// Remove the texture object from memory
	delete TextureToDestroy;
	TextureToDestroy = nullptr;

	AW_LOG("Game", "Texture has been destroyed.");
}

Text* Game::ImportText(const char* PathToFile)
{
	Text* NewText = new Text(m_RendererRef);

	if (!NewText->ImportTexture(PathToFile)) {
		delete NewText;
		return nullptr;
	}

	// Add texture to the texture stack
	m_TextStack.push_back(NewText);

	return NewText;
}

void Game::DestroyText(Text* TextToDestroy)
{
	// Iterate through each item and if it matches then remove it from array
	std::erase_if(m_TextStack,
		[TextToDestroy](const auto Item) { return Item == TextToDestroy; }
	);

	TextToDestroy->Cleanup();
	delete TextToDestroy;
}

Game::Game()
{
	printf("Game Created.\n");
	
	// Initalise Member Variables
	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;
	m_GameInput = nullptr;
	m_GameStateMachine = nullptr;
}

Game::~Game()
{
	printf("Game Destroyed.\n");
}

void Game::Initialise()
{
	// Run initialisation of dependencies
	// Initialise SDL and end the game if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		// If less than 0, initalisation has failed
		AW_LOG("Game", "SDL failed to init: " << SDL_GetError());
		return;
	}

	// Initialise fonts through ttf
	if (TTF_Init() == -1) {
		// If init is -1, initalisation has failed
		AW_LOG("Game", "TTF failed to init: " << TTF_GetError());
		Cleanup();
		return;
	}

	AW_LOG("Game", "Game successfully initialised all libraries.");

	Start();
}

void Game::Start()
{
	// Launch the game window
	// Create a window and check if it failed
	m_WindowRef = SDL_CreateWindow(
		"AWEngine",					// Window Title
		SDL_WINDOWPOS_CENTERED,		// Start X position on the screeen
		SDL_WINDOWPOS_CENTERED,		// Start Y position on the screeen
		1280, 720,					// Window resolution
		0							// Special window setting flags
	);							

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

	// Create the game input
	m_GameInput = new Input();

	// Create the game state machine
	m_GameStateMachine = new GameStateMachine(new PlayState());

	GameLoop();
}

void Game::GameLoop()
{
	// while IsGameOpen is true, keep the game running
	while (m_IsGameOpen)
	{
		PreLoop();
		ProcessInput();
		Update();
		Render();
		CollectGarbage();
	}

	Cleanup();
}

void Game::Cleanup()
{
	// Run the cleanup for the active game state
	m_GameStateMachine->Cleanup();

	for (const auto Item : m_TextStack) {
		Item->Cleanup();
		delete Item;
	}

	// Cleanup and remove all textures in the texture stack
	for (int i = m_TextureStack.size() - 1; i > -1; --i)
	{
		DestroyTexture(m_TextureStack[i]);
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

	TTF_Quit();
	SDL_Quit();

	AW_LOG("Game", "Game has deallocated all memory.");
}

void Game::PreLoop()
{
	// Runs the active game states pre loop
	m_GameStateMachine->PreLoop();
}

void Game::ProcessInput()
{
	// Process the inputs for the game
	m_GameInput->ProcessInput();

	// Process the input for the active game state
	m_GameStateMachine->ProcessInput(m_GameInput);
}

void Game::Update()
{
	// Record the previous frame time
	static double LastTickTime = 0.0;
	// Record the current frame time
	double CurrentTickTime = (double)SDL_GetTicks64();
	// Get the delta time - how much time has passed since the last frame
	double LongDelta = CurrentTickTime - LastTickTime;
	// Convert from milliseconds to seconds
	double DeltaTime = LongDelta / 1000.0;
	// Set the last tick time
	LastTickTime = CurrentTickTime;

	// Runs the active game states update
	m_GameStateMachine->Update(static_cast<float>(DeltaTime));

	// Caps the frame rate
	int FrameDuration = 1000 / 240;

	if ((double)FrameDuration > LongDelta) {
		FrameDuration = (int)LongDelta;
	}

	// If the frame rate is greater than 240, delay the frame
	SDL_Delay((Uint32)FrameDuration);
}

void Game::Render()
{
	// Tell the renderer the color used next
	SDL_SetRenderDrawColor(m_RendererRef, 50, 50, 80, 255);
	// Used the color to clear the previous frame
	SDL_RenderClear(m_RendererRef);

	// Render custom graphics
	// Draw all textures in the texture stack
	for (const auto TexRef : m_TextureStack) {
		if (TexRef != nullptr) {
			TexRef->Draw();
		}
	}

	// Draw text
	for (const auto Item : m_TextStack) {
		if (Item != nullptr) {
			Item->Draw();
		}
	}

	// Run the active game states render
	// Mostly just for debugging bounds
	m_GameStateMachine->Render(m_RendererRef);

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	// Runs the active game states garbage collection
	m_GameStateMachine->GarbageCollection();
}