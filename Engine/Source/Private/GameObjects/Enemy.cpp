#include "GameObjects/Enemy.h"
#include "Debug.h"

#define Super Character

#define SCALE 3.0f
#define SIZE ((48.0f - 16.0f) * SCALE)
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;
	
	// Add enemy base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Very damaged.png"
	);

	Bounds* EnemyBounds = AddBounds(0.0f, SIZE);
	EnemyBounds->m_OriginOffset = -HALF_SIZE;
	EnemyBounds->m_Tag = "ENEMY";
	EnemyBounds->m_Debug = true;
}

void Enemy::OnStart()
{
	Super::OnStart();

	//static float PositionX = 640.0f;
	//AW_LOG("Enemy", PositionX);
	//PositionX += 100.0f;

	// Start the enemy above the screen
	SetPosition({ 640.0f, -HALF_SIZE });
	// Flip the enemy to look downward
	SetRotation(180.0f);
	// Set the scale
	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().Position.y - HALF_SIZE > 720) {
		SetPosition({ 640.0f, -HALF_SIZE });
	}
}
