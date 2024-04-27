#pragma once
#include "EngineTypes.h"
#include "GameObjects/Background.h"
#include "SDL2/SDL_mixer.h"

class Input;
struct SDL_Renderer;
class GameObject;

class GameState {
public:
	GameState() : 
		m_ShouldDestroy(false), 
		m_Background(nullptr), 
		m_BGM(nullptr) {}

	virtual ~GameState() = default;

	// Runs when the game state starts
	void Start();

	// Cleanup and deallocate the memory for the state
	void Cleanup();

	// Runs every frame at the start of a game loop
	void PreLoop();

	// Detects input of the game
	void ProcessInput(Input* GameInput);

	// Update each frame after input
	void Update(float DeltaTime);

	// Render the game object bounds
	void Render(SDL_Renderer* Renderer);

	// Runs at the end of the frame and deallocates memory as needed
	void GarbageCollection();

	// Add a game object to the game
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject() {
		// Create the game object
		T* NewObject = new T();

		// Add the object to our pending spawn array
		m_GameObjectPendingSpawn.push_back(NewObject);

		return NewObject;
	}

	// Add a game object to the game with 1 parameter
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject(auto Param1) {
		// Create the game object
		T* NewObject = new T(Param1);

		// Add the object to our pending spawn array
		m_GameObjectPendingSpawn.push_back(NewObject);

		return NewObject;
	}

	// Add a game object to the game with 2 parameters
	template<class T, std::enable_if_t<std::is_base_of_v<GameObject, T>, T>* = nullptr>
	T* AddGameObject(auto Param1, auto Param2) {
		// Create the game object
		T* NewObject = new T(Param1, Param2);

		// Add the object to our pending spawn array
		m_GameObjectPendingSpawn.push_back(NewObject);

		return NewObject;
	}

	// Mark the game state for destroy at the end of the loop
	void DestroyGameState() { m_ShouldDestroy = true; }

	// Check if the game state is to be destroyed
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

protected:
	virtual void OnStart() {}

	virtual void OnCleanup() {}

	virtual void OnPreLoop() {}

	virtual void OnProcessInput(Input* GameInput) {}

	virtual void OnUpdate(float DeltaTime) {}

	virtual void OnGarbageCollection() {}

	void LoadMusic(const char* PathToFile) { m_BGM = Mix_LoadMUS(PathToFile); }

protected:
	// Background
	Background* m_Background;

	// Music
	Mix_Music* m_BGM;

private:
	// Store all game objects that need to be spawned on the next loop
	TArray<GameObject*> m_GameObjectPendingSpawn;

	// Store all of the game objects in the game
	TArray<GameObject*> m_GameObjectStack;

	// Mark for deletion
	bool m_ShouldDestroy;
};