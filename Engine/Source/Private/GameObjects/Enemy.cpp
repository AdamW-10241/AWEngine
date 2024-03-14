#include "GameObjects/Enemy.h"

#define Super Character

#define SCALE 3.0f
#define SIZE (48.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;
	
	// Add enemy base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Very damaged.png"
	);
}

void Enemy::OnStart()
{
	Super::OnStart();

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
