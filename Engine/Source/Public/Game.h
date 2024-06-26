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
class WinMenu;

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

	// Return the screen center
	Vector2 GetScreenCenter() const { return Vector2(WindowWidthF() / 2.0f, WindowHeightF() / 2.0f); }

	// Add a game object to the game
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject() {
		return GetGameStateMachine()->GetActiveGameState()->AddGameObject<T>();
	}

	// Add a game object to the game with 1 parameter
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject(auto Param1) {
		return GetGameStateMachine()->GetActiveGameState()->AddGameObject<T>(Param1);
	}

	// Add a game object to the game with 2 parameters
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject(auto Param1, auto Param2) {
		return GetGameStateMachine()->GetActiveGameState()->AddGameObject<T>(Param1, Param2);
	}

	// Add a game object to the game with 3 parameters
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject(auto Param1, auto Param2, auto Param3) {
		return GetGameStateMachine()->GetActiveGameState()->AddGameObject<T>(Param1, Param2, Param3);
	}

	// Restart the game to the default game state
	void RestartGame();

	// Get the windows menu
	WinMenu* GetWinMenu() const { return m_WinMenu; }

	// Get a random float value between 2 floats
	float GetRandomFloatRange(float min = 0.0f, float max = 1.0f) const;

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

	// Store the window menu for the game
	WinMenu* m_WinMenu;
};