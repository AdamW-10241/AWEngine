#include "GameObjects/Player.h"
#include "Input.h"

#define Super Character

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

Player::Player()
{
	// Default Values
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;

	// Add player base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png"
	);

	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 48;
	AnimParams.FrameWidth = 48;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add player sprite: right, idle
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParams
	));

	// Add player sprite: left, idle
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Add player sprite: up, idle
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Add player sprite: down, idle
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Add player sprite: right, moving
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParams
	));

	// Add player sprite: left, moving
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Add player sprite: up, moving
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Add player sprite: down, moving
	m_DirectionSprites.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	SetAnimation(DIRECTION_UP, true);
}

void Player::OnStart()
{
	Super::OnStart();
	
	SetPosition({ 640.0f, 360.0f });
	SetScale(3.0f);
}

void Player::OnProcessInput(Input* GameInput)
{
	Super::OnProcessInput(GameInput);
	
	if (GameInput->IsKeyDown(AW_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_A)) {
		AddMovementInput(Vector2(-1.0f, 0.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_D)) {
		AddMovementInput(Vector2(1.0f, 0.0f));
	}
}

void Player::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Get the player idle state
	bool IdleState;

	if (m_MoveDirection.Length() > 0.0f) {
		IdleState = true;
	}
	else {
		IdleState = false;
	}

	// Set the player animation
	if (m_MoveDirection.x > 0) {
		SetAnimation(DIRECTION_RIGHT, IdleState);
	}
	else if (m_MoveDirection.x < 0) {
		SetAnimation(DIRECTION_LEFT, IdleState);
	}	
	else if (m_MoveDirection.y > 0) {
		SetAnimation(DIRECTION_UP, IdleState);
	}
	else if (m_MoveDirection.y < 0) {
		SetAnimation(DIRECTION_DOWN, IdleState);
	}
}

void Player::SetAnimation(uint32_t Direction, bool IdleState)
{
	// Check all sprites are non nullptr
	if (m_DirectionSprites.size() > 7) {
		for (int Sprite = 0; Sprite < 8; Sprite++) {
			if (m_DirectionSprites[Sprite] == nullptr) {
				return;
			}
		}
	}

	// Set all direction sprites (idle and moving) to inactive
	for (int Sprite = 0; Sprite < 8; Sprite++) {
		m_DirectionSprites[Sprite]->SetActive(false);
	}

	// Activate the correct direction sprite (idle and moving)
	// + 4 when the idle state is moving to get the latter moving sprites
	m_DirectionSprites[Direction + !IdleState * 4]->SetActive(true);
}
