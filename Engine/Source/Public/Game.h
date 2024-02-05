#pragma once

class Game {
public:
	// Get the game singleton or create one if it does not exist
	static Game* GetGame();
	// Deallocate the game from memory
	static void DestroyGame();
	// Run the game
	void Run() { Initialise(); }

private:
	// Constructor runs when the class is created
	// Need it to create a new object
	Game();
	// Destructor runs when the class is destroyed/deleted
	~Game();

	// Core Game Functions
	// Initialise the dependencies/external libraries
	// This will exit the game if any fail
	void Initialise();
	// This will run the post-initialise function that rely on dependencies
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
};