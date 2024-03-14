#include "GameObjects/Player.h"
#include "Input.h"

#define Super DirectionalCharacter

Player::Player()
{
	// Default Values
	m_MaxSpeed = 400.0f;
	m_Deceleration = 7.0f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams AnimParams;
	AnimParams.fps = 12;
	AnimParams.FrameHeight = 16;
	AnimParams.FrameWidth = 16;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add player sprite: idle, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Right.png"
	));

	// Add player sprite: idle, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Left.png"
	));

	// Add player sprite: idle, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Up.png"
	));

	// Add player sprite: idle, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Down.png"
	));

	// Add player sprite: moving, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Right.png",
		&AnimParams
	));

	// Add player sprite: moving, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Left.png",
		&AnimParams
	));

	// Add player sprite: moving, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Up.png",
		&AnimParams
	));

	// Add player sprite: moving, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Down.png",
		&AnimParams
	));

	// Set base animation state
	m_LastMovementDirection = DIRECTION_DOWN;
	SetAnimation(m_LastMovementDirection, true);
}

void Player::OnStart()
{
	Super::OnStart();
	
	SetPosition({ 640.0f, 360.0f });
	SetScale(4.0f);
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
}
