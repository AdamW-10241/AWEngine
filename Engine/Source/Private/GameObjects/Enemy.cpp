#include "GameObjects/Enemy.h"

#define Super DirectionalCharacter

#define SCALE 4.0f
#define SIZE (16.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy()
{
	// Default Values
	m_MaxSpeed = 100.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 1000.0f;

	m_TimeUntilNextMovementChoice = 0.0f;

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

	// Set starting position
	static float StartingPosition(0.0f);
	SetPosition({ 640.0f, StartingPosition });
	StartingPosition += 40.0f;

	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltaTime)
{
	// Randomly choose movement
	if (m_TimeUntilNextMovementChoice - DeltaTime <= 0.0f) {
		// Randomly determine movement direction
		m_MovementChoice = { (float)((rand() % 3) - 1), (float)((rand() % 3) - 1) };
		// Randomly get time until next choice
		m_TimeUntilNextMovementChoice = rand() % 4;
	}
	
	// Reduce time until choice
	m_TimeUntilNextMovementChoice -= DeltaTime;

	// Add movement
	AddMovementInput(m_MovementChoice);

	Super::OnUpdate(DeltaTime);

	// Screen Wrap
	ScreenWrap(HALF_SIZE);
}
