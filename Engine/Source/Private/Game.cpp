#include "Game.h"
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Input.h"
#include "GameObjects/GameObject.h"

// DEBUG
#include "GameObjects/PhysicsObject.h"
#include "Math/Vector2.h"
#include "Graphics/Animation.h"

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

template<typename T>
T* Game::AddGameObject()
{
	// Create the game object
	T* NewObject = new T();

	// Add the object to our pending spawn array
	m_GameObjectPendingSpawn.push_back(NewObject);
	
	return NewObject;
}

Game::Game()
{
	printf("Game Created.\n");
	
	// Initalise Member Variables
	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;
	m_GameInput = nullptr;

	// DEBUG VARS
	m_TestAnim1 = nullptr;
	m_TestObject = nullptr;
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

	// Create the game input
	m_GameInput = new Input();
	
	// DEBUG
	m_TestObject = AddGameObject<PhysicsObject>();

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
	// Destroy any objects pending spawn
	for (auto GO : m_GameObjectPendingSpawn) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}

	// Destroy any remaining game objects
	for (auto GO : m_GameObjectStack) {
		GO->Cleanup();
		delete GO;
		GO = nullptr;
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

	SDL_Quit();

	AW_LOG("Game", "Game has deallocated all memory.");
}

void Game::PreLoop()
{
	// Add all game object pending spawn to the game object stack
	for (auto GO : m_GameObjectPendingSpawn) {
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	// Resize the array to 0
	m_GameObjectPendingSpawn.clear();
}

void Game::ProcessInput()
{
	// Process the inputs for the game
	m_GameInput->ProcessInput();

	// Run the input listener function for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->ProcessInput(m_GameInput);
		}
	}
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

	//// DEBUG
	//// Position of the animation on the screen
	//static Vector2 Position(640.0f, 360.0f);
	//// Speed of the movement
	//float Speed(200.0f * (float)DeltaTime);
	//// Direction to move in
	//Vector2 MovementDirection(0.0f);

	//if (m_GameInput->IsKeyDown(AW_KEY_W))
	//{
	//	MovementDirection.y += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(AW_KEY_S))
	//{
	//	MovementDirection.y += 1.0f;
	//}
	//if (m_GameInput->IsKeyDown(AW_KEY_A))
	//{
	//	MovementDirection.x += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(AW_KEY_D))
	//{
	//	MovementDirection.x += 1.0f;
	//}
	//if (m_GameInput->IsKeyDown(AW_KEY_Q))
	//{
	//	if (m_TestObject != nullptr) {
	//		m_TestObject->DestroyObject();
	//		m_TestObject = nullptr;
	//	}
	//}

	//// Move the animation to the right
	//Position += MovementDirection * Speed;

	//// TODO: Update Game Logic
	// Run the update logic for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->Update((float)DeltaTime);
			GO->PostUpdate((float)DeltaTime);
		}
	}
}

void Game::Render()
{
	// Tell the renderer the color used next
	SDL_SetRenderDrawColor(m_RendererRef, 50, 50, 80, 255);
	// Used the color to clear the previous frame
	SDL_RenderClear(m_RendererRef);

	// TODO: Render custom graphics
	// Draw all textures in the texture stack
	for (Texture* TexRef : m_TextureStack)
	{
		if (TexRef != nullptr)
		{
			TexRef->Draw();
		}
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	// TODO: Delete Objects at the end of each frame.
	for (int i = m_GameObjectStack.size() - 1; i >= 0; --i) {
		if (!m_GameObjectStack[i]->IsPendingDestroy()) {
			continue;
		}

		// Make sure the game object isn't nullptr
		if (m_GameObjectStack[i] != nullptr) {
			m_GameObjectStack[i]->Cleanup();
			delete m_GameObjectStack[i];
		}

		// Remove from and resize the array
		m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
	}
}