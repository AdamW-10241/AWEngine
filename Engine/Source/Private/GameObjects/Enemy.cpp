#include "GameObjects/Enemy.h"
#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include "GameObjects/Player.h"

#include "Debug.h"

#define Super DirectionalCharacter

#define SCALE 4.0f
#define SIZE (16.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy() : m_TimeUntilNextMovementChoice(0.0f), m_ScoreValue(250.0f), m_PlayerRef(nullptr)
{
	// Default Values
	m_MaxSpeed = 150.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 1000.0f;

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

	// Add bounds
	Bounds* EnemyBounds = AddBounds(0.0f, SIZE);
	EnemyBounds->m_OriginOffset = -HALF_SIZE;
	EnemyBounds->m_Tag = "ENEMY";
	EnemyBounds->m_Debug = false;
}

void Enemy::OnStart()
{
	Super::OnStart();

	// Get player reference
	m_PlayerRef = PlayState::GetPlayer();

	// Pick random spawn spot
	SetPosition({(float)(rand() % 1280), 25.0f});

	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltaTime)
{
	// Randomly choose movement
	if (m_TimeUntilNextMovementChoice - DeltaTime <= 0.0f) {
		// Check player is valid
		if (m_PlayerRef == nullptr) {
			return;
		}

		// Randomly determine movement direction
		if (rand() % 3 <= 1) {
			// Toward player
			// 2/3 to follow
			m_MovementChoice = (*m_PlayerRef).GetTransform().Position - GetTransform().Position;
		}
		else {
			// Random direction
			// 1/3 to move randomly
			m_MovementChoice = { (float)((rand() % 3) - 1), (float)((rand() % 3) - 1) };
		}
		
		// Randomly get time until next choice
		m_TimeUntilNextMovementChoice = rand() % 4;
	}

	// Reduce time until choice
	m_TimeUntilNextMovementChoice -= DeltaTime;

	// Add movement
	AddMovementInput(m_MovementChoice);

	Super::OnUpdate(DeltaTime);

	// Screen border
	ScreenBorder(HALF_SIZE);
}

void Enemy::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->m_Tag == "PROJECTILE") {
		// Destroy projectile
		OverlapBounds->GetOwner()->DestroyObject();

		// Add score
		PlayState::AddScore(m_ScoreValue);

		// Random chance to spawn a collectable
		// 1/3 chance
		if (rand() % 3 == 0) {
			PlayState::SpawnCollectable(GetTransform().Position);
		}

		// Destroy enemy
		DestroyObject();
	}
}
