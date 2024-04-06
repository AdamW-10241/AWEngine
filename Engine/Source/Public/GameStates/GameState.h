#pragma once
#include "EngineTypes.h"

class Input;
struct SDL_Renderer;
class GameObject;
class Background;

class GameState {
public:
	GameState() : m_ShouldDestroy(false), m_Background(nullptr) {}
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
	template<class T>
	T* AddGameObject() {
		// Create the game object
		T* NewObject = new T();

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

protected:
	// Background
	Background* m_Background;

private:
	// Store all game objects that need to be spawned on the next loop
	TArray<GameObject*> m_GameObjectPendingSpawn;

	// Store all of the game objects in the game
	TArray<GameObject*> m_GameObjectStack;

	// Mark for deletion
	bool m_ShouldDestroy;
};
