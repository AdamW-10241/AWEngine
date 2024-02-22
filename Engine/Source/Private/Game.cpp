#include "Game.h"
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

// DEBUG
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

Game::Game()
{
	printf("Game Created.\n");
	
	// Initalise Member Variables
	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	// Assessment 1 Animations & Sprites
	m_AnimBackground = nullptr;
	m_AnimWatermill = nullptr;
	m_AnimMillHouse = nullptr;
	m_AnimMillPropeller = nullptr;
	m_AnimChicken1 = nullptr;
	m_AnimChicken2 = nullptr;
	m_AnimPig = nullptr;
	m_AnimPlant1 = nullptr;
	m_AnimPlant2 = nullptr;
	m_AnimPlant3 = nullptr;
	m_AnimFlag = nullptr;
	m_AnimWaterRipple = nullptr;
	m_AnimLeaf1 = nullptr;
	m_AnimLeaf2 = nullptr;
	m_AnimFrog = nullptr;
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

	// Assessment 1 Animations & Sprites
	// Background
	AnimationParams AnimParamsBackground;
	AnimParamsBackground.FrameWidth = 1440;
	AnimParamsBackground.FrameHeight = 816;

	m_AnimBackground = new Animation();
	m_AnimBackground->CreateAnimation(
		"Content/NinjaAdventure/Custom Background/BackgroundWater.png",
		&AnimParamsBackground
	);

	m_AnimBackground->SetPosition(1280.0 / 2.0, 720.0 / 2.0);
	m_AnimBackground->SetScale(0.9);

	// Watermill
	AnimationParams AnimParamsWatermill;
	AnimParamsWatermill.fps = 8.0f;
	AnimParamsWatermill.StartFrame = 0;
	AnimParamsWatermill.MaxFrames = 3;
	AnimParamsWatermill.EndFrame = 2;
	AnimParamsWatermill.FrameWidth = 34;
	AnimParamsWatermill.FrameHeight = 36;

	m_AnimWatermill = new Animation();
	m_AnimWatermill->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/WaterMill/Watermill_B_34x36.png",
		&AnimParamsWatermill
	);

	m_AnimWatermill->SetPosition(1000.0, 350.0);
	m_AnimWatermill->SetScale(3.0);

	// Mill House
	AnimationParams AnimParamsMillHouse;
	AnimParamsMillHouse.FrameWidth = 3 * 16;
	AnimParamsMillHouse.FrameHeight = 4 * 16;
	AnimParamsMillHouse.ClipX = 29 * 16;
	AnimParamsMillHouse.ClipY = 4 * 16;

	m_AnimMillHouse = new Animation();
	m_AnimMillHouse->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Tilesets/TilesetHouse.png",
		&AnimParamsMillHouse
	);

	m_AnimMillHouse->SetPosition(850.0, 300.0);
	m_AnimMillHouse->SetScale(4.0);

	// Mill Propeller
	AnimationParams AnimParamsMillPropeller;
	AnimParamsMillPropeller.fps = 4.0f;
	AnimParamsMillPropeller.StartFrame = 0;
	AnimParamsMillPropeller.MaxFrames = 4;
	AnimParamsMillPropeller.EndFrame = 3;
	AnimParamsMillPropeller.FrameWidth = 64;
	AnimParamsMillPropeller.FrameHeight = 64;

	m_AnimMillPropeller = new Animation();
	m_AnimMillPropeller->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/MillPropeller/MillPropeller_B_64x64.png",
		&AnimParamsMillPropeller
	);

	m_AnimMillPropeller->SetPosition(850.0, 275.0);
	m_AnimMillPropeller->SetScale(4.0);

	// Chicken 1
	AnimationParams AnimParamsChicken1;
	AnimParamsChicken1.fps = 5.0f;
	AnimParamsChicken1.StartFrame = 0;
	AnimParamsChicken1.MaxFrames = 2;
	AnimParamsChicken1.EndFrame = 1;
	AnimParamsChicken1.FrameWidth = 16;
	AnimParamsChicken1.FrameHeight = 16;

	m_AnimChicken1 = new Animation();
	m_AnimChicken1->CreateAnimation(
		"Content/NinjaAdventure/Actor/Animals/Chicken/SpriteSheetBlack.png",
		&AnimParamsChicken1
	);

	m_AnimChicken1->SetPosition(100.0, 300.0);
	m_AnimChicken1->SetScale(2.5);

	// Chicken 2
	AnimationParams AnimParamsChicken2;
	AnimParamsChicken2.fps = 5.0f;
	AnimParamsChicken2.StartFrame = 0;
	AnimParamsChicken2.MaxFrames = 2;
	AnimParamsChicken2.EndFrame = 1;
	AnimParamsChicken2.FrameWidth = 16;
	AnimParamsChicken2.FrameHeight = 16;

	m_AnimChicken2 = new Animation();
	m_AnimChicken2->CreateAnimation(
		"Content/NinjaAdventure/Actor/Animals/Chicken/SpriteSheetBrown.png",
		&AnimParamsChicken1
	);

	m_AnimChicken2->SetPosition(150.0, 375.0);
	m_AnimChicken2->SetScale(2.5);

	// Pig
	AnimationParams AnimParamsPig;
	AnimParamsPig.fps = 3.0f;
	AnimParamsPig.StartFrame = 0;
	AnimParamsPig.MaxFrames = 2;
	AnimParamsPig.EndFrame = 1;
	AnimParamsPig.FrameWidth = 16;
	AnimParamsPig.FrameHeight = 16;

	m_AnimPig = new Animation();
	m_AnimPig->CreateAnimation(
		"Content/NinjaAdventure/Actor/Animals/Pig/SpriteSheetPink.png",
		&AnimParamsPig
	);

	m_AnimPig->SetPosition(200.0, 450.0);
	m_AnimPig->SetScale(3.0);

	// Plant 1
	AnimationParams AnimParamsPlant;
	AnimParamsPlant.fps = 2.0f;
	AnimParamsPlant.StartFrame = 0;
	AnimParamsPlant.MaxFrames = 4;
	AnimParamsPlant.EndFrame = 3;
	AnimParamsPlant.FrameWidth = 16;
	AnimParamsPlant.FrameHeight = 16;

	m_AnimPlant1 = new Animation();
	m_AnimPlant1->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/Plant/SpriteSheet16x16.png",
		&AnimParamsPlant
	);

	m_AnimPlant1->SetPosition(800.0, 580.0);
	m_AnimPlant1->SetScale(3.0);

	// Plant 2
	m_AnimPlant2 = new Animation();
	m_AnimPlant2->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/Plant/SpriteSheet16x16.png",
		&AnimParamsPlant
	);

	m_AnimPlant2->SetPosition(875.0, 520.0);
	m_AnimPlant2->SetScale(3.0);

	// Plant 3
	m_AnimPlant3 = new Animation();
	m_AnimPlant3->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/Plant/SpriteSheet16x16.png",
		&AnimParamsPlant
	);

	m_AnimPlant3->SetPosition(900.0, 610.0);
	m_AnimPlant3->SetScale(3.0);

	// Flag
	AnimationParams AnimParamsFlag;
	AnimParamsFlag.fps = 4.0f;
	AnimParamsFlag.StartFrame = 0;
	AnimParamsFlag.MaxFrames = 4;
	AnimParamsFlag.EndFrame = 3;
	AnimParamsFlag.FrameWidth = 16;
	AnimParamsFlag.FrameHeight = 16;

	m_AnimFlag = new Animation();
	m_AnimFlag->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/Flag/FlagBlue16x16.png",
		&AnimParamsFlag
	);

	m_AnimFlag->SetPosition(1200.0, 590.0);
	m_AnimFlag->SetScale(3.0);

	// Water Ripple
	AnimationParams AnimParamsWaterRipple;
	AnimParamsWaterRipple.fps = 4.0f;
	AnimParamsWaterRipple.StartFrame = 0;
	AnimParamsWaterRipple.MaxFrames = 4;
	AnimParamsWaterRipple.EndFrame = 3;
	AnimParamsWaterRipple.FrameWidth = 16;
	AnimParamsWaterRipple.FrameHeight = 16;

	m_AnimWaterRipple = new Animation();
	m_AnimWaterRipple->CreateAnimation(
		"Content/NinjaAdventure/Backgrounds/Animated/Water Ripples/SpriteSheet16x16.png",
		&AnimParamsWaterRipple
	);

	m_AnimWaterRipple->SetPosition(700.0, 680.0);
	m_AnimWaterRipple->SetScale(4.0);

	// Leaf 1
	AnimationParams AnimParamsLeaves;
	AnimParamsLeaves.fps = 5.0f;
	AnimParamsLeaves.StartFrame = 3;
	AnimParamsLeaves.MaxFrames = 6;
	AnimParamsLeaves.EndFrame = 5;
	AnimParamsLeaves.FrameWidth = 12;
	AnimParamsLeaves.FrameHeight = 7;

	m_AnimLeaf1 = new Animation();
	m_AnimLeaf1->CreateAnimation(
		"Content/NinjaAdventure/FX/Particle/Leaf.png",
		&AnimParamsLeaves
	);

	m_AnimLeaf1->SetPosition(830.0, 105.0);
	m_AnimLeaf1->SetScale(3.0);

	// Leaf 2
	m_AnimLeaf2 = new Animation();
	m_AnimLeaf2->CreateAnimation(
		"Content/NinjaAdventure/FX/Particle/Leaf.png",
		&AnimParamsLeaves
	);

	m_AnimLeaf2->SetPosition(1080.0, 150.0);
	m_AnimLeaf2->SetScale(2.8);

	// Frog
	AnimationParams AnimParamsFrog;
	AnimParamsFrog.fps = 4.5f;
	AnimParamsFrog.StartFrame = 0;
	AnimParamsFrog.MaxFrames = 2;
	AnimParamsFrog.EndFrame = 1;
	AnimParamsFrog.FrameWidth = 16;
	AnimParamsFrog.FrameHeight = 16;

	m_AnimFrog = new Animation();
	m_AnimFrog->CreateAnimation(
		"Content/NinjaAdventure/Actor/Animals/Frog/SpriteSheet.png",
		&AnimParamsFrog
	);

	m_AnimFrog->SetPosition(480.0, 600.0);
	m_AnimFrog->SetScale(3.0);

	// Game Loop
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

	// Update Game Logic
	// Assessment 1 Animations & Sprites
	// No need to update the backdrop
	if (m_AnimWatermill != nullptr)
	{
		m_AnimWatermill->Update((float)DeltaTime);
	}
	if (m_AnimMillPropeller != nullptr)
	{
		m_AnimMillPropeller->Update((float)DeltaTime);
	}
	// No need to update the house
	if (m_AnimChicken1 != nullptr)
	{
		m_AnimChicken1->Update((float)DeltaTime);
		m_AnimChicken1->MoveXBetween(100.0f, 350.0f, 6.0f, (float)DeltaTime);
	}
	if (m_AnimChicken2 != nullptr)
	{
		m_AnimChicken2->Update((float)DeltaTime);
		m_AnimChicken2->MoveXBetween(150.0f, 400.0f, 7.0f, (float)DeltaTime);
	}
	if (m_AnimPig != nullptr)
	{
		m_AnimPig->Update((float)DeltaTime);
		m_AnimPig->MoveXBetween(200.0f, 400.0f, 10.0f, (float)DeltaTime);
	}
	if (m_AnimPlant1 != nullptr)
	{
		m_AnimPlant1->Update((float)DeltaTime);
	}
	if (m_AnimPlant2 != nullptr)
	{
		m_AnimPlant2->Update((float)DeltaTime);
	}
	if (m_AnimPlant3 != nullptr)
	{
		m_AnimPlant3->Update((float)DeltaTime);
	}
	if (m_AnimFlag != nullptr)
	{
		m_AnimFlag->Update((float)DeltaTime);
	}
	if (m_AnimWaterRipple != nullptr)
	{
		m_AnimWaterRipple->Update((float)DeltaTime);
	}
	if (m_AnimLeaf1 != nullptr)
	{
		m_AnimLeaf1->Update((float)DeltaTime);
		m_AnimLeaf1->Rotate(3.0f, (float)DeltaTime);
	}
	if (m_AnimLeaf2 != nullptr)
	{
		m_AnimLeaf2->Update((float)DeltaTime);
		m_AnimLeaf2->Rotate(-4.5f, (float)DeltaTime);
	}
	if (m_AnimFrog != nullptr)
	{
		m_AnimFrog->Update((float)DeltaTime);
		m_AnimFrog->MoveXBetween(500.0f, 550.0f, 2.0f, (float)DeltaTime);
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
}
