#pragma once
#include "EngineTypes.h"
#include "GameStates/GameStateMachine.h"

// Forward Declaration
struct SDL_Window;
struct SDL_Renderer;
class Texture;
class Input;
class GameObject;
class Text;

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

	// Import text to the game
	Text* ImportText(const char* PathToFile);

	// Safe destroy the text
	void DestroyText(Text* TextToDestroy);

	// Gets the game state machine
	GameStateMachine* GetGameStateMachine() const { return m_GameStateMachine; }

	// Return the width of the window
	int WindowWidth() const;

	// Return the height of the window
	int WindowHeight() const;

	// Return the width of the window as a float
	float WindowWidthF() const;

	// Return the height of the window as a float
	float WindowHeightF() const;

	// Add a game object to the game
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject() {
		return GetGameStateMachine()->GetActiveGameState()->AddGameObject<T>();
	}

public:
	// Score for the game
	int m_Score;

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
	// Checks if any objects need to be spawned
	void PreLoop();

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

	// Stores all text elements
	TArray<Text*> m_TextStack;

	// Store the input handler for the game
	Input* m_GameInput;

	// Game state machine for the game
	GameStateMachine* m_GameStateMachine;
};