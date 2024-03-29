#include "GameObjects/Projectile.h"
#include "GameObjects/Enemy.h"

#define Super Character

#define SCALE 3.0f
#define SIZE ((48.0f - 16.0f) * SCALE)
#define HALF_SIZE (SIZE / 2.0f)

Projectile::Projectile(Vector2 AimPosition)
{
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;

	// Add base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship Weapons/PNGs/Main ship weapon - Projectile - Rocket.png"
	);

	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 32;
	AnimParams.FrameWidth = 32;
	AnimParams.EndFrame = 2;
	AnimParams.MaxFrames = 3;

	Bounds* ProjectileBounds = AddBounds({ 640.0f, 360.0f }, SIZE);
	ProjectileBounds->m_OriginOffset = -HALF_SIZE;
	ProjectileBounds->m_Debug = true;
}

void Projectile::OnStart()
{
	Super::OnStart();

	SetPosition({ 640.0f, 360.0f });
	SetScale(SCALE);
}

void Projectile::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
}

void Projectile::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	/*
	if (dynamic_cast<Enemy*>(OverlapBounds->GetOwner())) {
		OverlapBounds->GetOwner()->DestroyObject();
	}
	*/
}
