#include "GameStates/GameState.h"
#include "GameObjects/GameObject.h"
#include "Math/Bounds.h"
#include "SDL2/SDL_render.h"

void GameState::Start()
{	
	OnStart();

	// Play background music
	if (m_BGM != nullptr) {
		Mix_PlayMusic(m_BGM, -1);
		Mix_VolumeMusic(80);
	}
}

void GameState::Cleanup()
{
	OnCleanup();

	// Free music
	if (m_BGM != nullptr) {
		Mix_FreeMusic(m_BGM);
	}

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
}

void GameState::PreLoop()
{
	// Add all game object pending spawn to the game object stack
	for (auto GO : m_GameObjectPendingSpawn) {
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	// Resize the array to 0
	m_GameObjectPendingSpawn.clear();

	OnPreLoop();
}

void GameState::ProcessInput(Input* GameInput)
{
	// Run the input listener function for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->ProcessInput(GameInput);
		}
	}
	
	OnProcessInput(GameInput);
}

void GameState::Update(float DeltaTime)
{
	// Run the update logic for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->Update(DeltaTime);
			GO->PostUpdate(DeltaTime);

			// Looking through all of the other game objects
			for (auto OtherGO : m_GameObjectStack) {
				// Running through all of the other game object bounds
				for (auto OtherBounds : OtherGO->GetAllBounds()) {
					// Testing the bounds for overlapping events
					GO->TestOverLapEvent(OtherBounds);
				}
			}
		}
	}
	
	OnUpdate(DeltaTime);
}

void GameState::Render(SDL_Renderer* Renderer)
{
	// Render bounds if marked debug
	for (auto GO : m_GameObjectStack) {
		if (GO == nullptr) {
			continue;
		}

		// Loop through all the game object bounds
		for (auto TestBounds : GO->GetAllBounds()) {
			// If debug us false then skip the next bounds
			if (!TestBounds->m_Debug) {
				continue;
			}

			// Set the colour of the next drawn thing in SDL
			// in this case, the bounds
			SDL_SetRenderDrawColor(
				Renderer,
				TestBounds->m_RenderColour.r,
				TestBounds->m_RenderColour.g,
				TestBounds->m_RenderColour.b,
				255
			);

			// Converting the AWRect to a SDL_FRect
			SDL_FRect BoundsRect{
				TestBounds->GetCenter().x,
				TestBounds->GetCenter().y,
				TestBounds->m_Rect.Extent.x,
				TestBounds->m_Rect.Extent.y
			};

			// Draws a rectangle to the window
			SDL_RenderDrawRectF(Renderer, &BoundsRect);
		}
	}
}

void GameState::GarbageCollection()
{
	OnGarbageCollection();

	// Collect the garbage on a game object level
	for (const auto GO : m_GameObjectStack) {
		GO->CollectGarbage();
	}

	// Delete Objects at the end of each frame
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