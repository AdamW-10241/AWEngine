#include "GameObjects/Enemy.h"

#define Super DirectionalCharacter

#define SCALE 4.0f
#define SIZE (16.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy()
{
	// Default Values
	m_MaxSpeed = 200.0f;
	m_Deceleration = 7.0f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams AnimParams;
	AnimParams.fps = 12;
	AnimParams.FrameHeight = 16;
	AnimParams.FrameWidth = 16;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add enemy sprite: idle, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Right.png"
	));

	// Add enemy sprite: idle, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Left.png"
	));

	// Add enemy sprite: idle, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Up.png"
	));

	// Add enemy sprite: idle, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Down.png"
	));

	// Add enemy sprite: moving, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Right.png",
		&AnimParams
	));

	// Add enemy sprite: moving, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Left.png",
		&AnimParams
	));

	// Add enemy sprite: moving, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Up.png",
		&AnimParams
	));

	// Add enemy sprite: moving, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Down.png",
		&AnimParams
	));

	// Set base animation state
	m_LastMovementDirection = DIRECTION_DOWN;
	SetAnimation(m_LastMovementDirection, true);
}

void Enemy::OnStart()
{
	Super::OnStart();

	// Start the enemy above the screen
	SetPosition({ 640.0f, 360.0f });
	// Set the scale
	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltaTime)
{
	AddMovementInput(Vector2(-1.0f, 0.0f));
	
	Super::OnUpdate(DeltaTime);

	// Screen Wrapping
	// Bottom to top
	if (GetTransform().Position.y - HALF_SIZE > 720) {
		SetPosition({ GetTransform().Position.x, -HALF_SIZE });
	}
	// Top to bottom
	if (GetTransform().Position.y + HALF_SIZE < -HALF_SIZE ) {
		SetPosition({ GetTransform().Position.x, 720 + HALF_SIZE });
	}
	// Right to left
	if (GetTransform().Position.x - HALF_SIZE > 1280) {
		SetPosition({ -HALF_SIZE, GetTransform().Position.y });
	}
	// Left to right
	if (GetTransform().Position.x + HALF_SIZE < -HALF_SIZE) {
		SetPosition({ 1280 + HALF_SIZE, GetTransform().Position.y });
	}
}
