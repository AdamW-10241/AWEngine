#include "GameObjects/Projectile.h"

#include "Debug.h"

#define Super Character

#define SCALE 1.3f
#define SIZE (23.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

Projectile::Projectile()
{
	// Default Values
	m_MaxSpeed = 750.0f;
	m_Drag = 0.0f;
	m_Deceleration = 0.0f;
	m_AccelerationSpeed = 5000.0f;
	
	// Main sprite
	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 23;
	AnimParams.FrameWidth = 23;
	AnimParams.EndFrame = 1;
	AnimParams.MaxFrames = 2;

	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/FX/Projectile/BigShuriken.png",
		&AnimParams
	);

	// Add bounds
	Bounds* CollectableBounds = AddBounds(0.0f, SIZE);
	CollectableBounds->m_OriginOffset = -HALF_SIZE;
	CollectableBounds->m_Tag = "PROJECTILE";
	CollectableBounds->m_Debug = false;
}

void Projectile::OnStart()
{
	Super::OnStart();

	SetScale(SCALE);
}

void Projectile::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	DestroyOffScreen(HALF_SIZE);
}

void Projectile::DestroyOffScreen(float HalfSpriteSize)
{
	// Destroy the projectile if it goes offscreen
	Vector2 ProjectilePosition = GetTransform().Position;

	if ((ProjectilePosition.y - HalfSpriteSize > 720) ||
		(ProjectilePosition.y + HalfSpriteSize < -HalfSpriteSize) ||
		(ProjectilePosition.x - HalfSpriteSize > 1280) ||
		(ProjectilePosition.x + HalfSpriteSize < -HalfSpriteSize)
	){
		DestroyObject();
		AW_LOG("Projectile", "Destroyed offscreen.");
	}
}
