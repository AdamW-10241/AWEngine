#pragma once
#include "EngineTypes.h"

// Forward Declaration
struct SDL_Window;
struct SDL_Renderer;
class Texture;

// DEBUG
class Animation;

class Game {
public:
	// Get the game singleton or create one if it does not exist
	static Game* GetGame();
	// Deallocate the game from memory
	static void DestroyGame();
	// Run the game
	void Run() { Initialise(); }
	// Exit the app
	void QuitApp() { m_IsGameOpen = false; }
	// Import a texture to the game
	Texture* ImportTexture(const char* PathToFile);
	// Safe destroy the texture
	void DestroyTexture(Texture* TextureToDestroy);

private:
	// Constructor runs when the class is created
	// Need it to create a new object
	Game();
	// Destructor runs when the class is destroyed/deleted
	~Game();

	// Core Game Functions
	// Initialise the dependencies/external libraries
	// Exit the game if any fail
	void Initialise();
	// Run the post-initialise function that rely on dependencies
	// Load the window and any start game functions
	void Start();
	// Run the game loop functions of the game until the app closes
	void GameLoop();
	// Deallocate memory after the game loop has been exited
	void Cleanup();

	// Game Loop
	// Listen for user input and process it
	void ProcessInput();
	// Update the game logic based on user inputs
	void Update();
	// Display the results and render graphics based on logic
	void Render();
	// Any objects marked for deletion will be deallocated from memory here
	void CollectGarbage();

private:
	// Flag that decides when the game loop ends
	bool m_IsGameOpen;
	// Stores the window for the app/game
	SDL_Window* m_WindowRef;
	// Stores the renderer for the SDL window
	SDL_Renderer* m_RendererRef;
	// Stores all of the textures in the game
	TArray<Texture*> m_TextureStack;

	// Assessment 1 Animations & Sprites
	Animation* m_AnimBackground;
	Animation* m_AnimWatermill;
	Animation* m_AnimMillHouse;
	Animation* m_AnimMillPropeller;
	Animation* m_AnimChicken1;
	Animation* m_AnimChicken2;
	Animation* m_AnimPig;
	Animation* m_AnimPlant1;
	Animation* m_AnimPlant2;
	Animation* m_AnimPlant3;
	Animation* m_AnimFlag;
	Animation* m_AnimWaterRipple;
	Animation* m_AnimLeaf1;
	Animation* m_AnimLeaf2;
	Animation* m_AnimFrog;
};