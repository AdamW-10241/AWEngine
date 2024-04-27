#include "GameObjects/Weapons/Arrow.h"
#include "GameObjects/VFX/VFX_ArrowHit.h"
#include "GameObjects/VFX/VFX_ArrowMiss.h"
#include "GameObjects/DirectionalCharacter.h"

#include "Game.h"

Arrow::Arrow(float Scale)
{
	// Set variables
	m_Scale = Scale;

	m_MaxSpeed = 1000.0f;

	// Set the scale
	SetScale(m_Scale);

	m_Bounds->SetBoundsExtent(ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Debug = false;
}

void Arrow::OnStart()
{
	// Add sprite
	if (m_ToggleSprite) {
		// Toggled
		AnimationParams AnimParams;
		AnimParams.fps = 12;
		AnimParams.FrameHeight = 16;
		AnimParams.FrameWidth = 16;
		AnimParams.EndFrame = 3;
		AnimParams.MaxFrames = 4;

		m_Size = 16.0f;
		m_MainSprite = AddSprite("Content/NinjaAdventure/FX/Projectile/Fireball.png", &AnimParams);
	}
	else {
		// Default
		m_Size = 15.0f;
		m_MainSprite = AddSprite("Content/NinjaAdventure/Items/Weapons/Bow/Arrow.png");
	}
}

void Arrow::CreateHitVFX(Vector2 Position)
{
	// Create arrow hit VFX
	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_ArrowHit>();
	VFX->SetPosition(Position);
	VFX->SetScale(m_Scale);
}

void Arrow::CreateMissVFX(Vector2 Position)
{
	// Create arrow miss VFX
	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_ArrowMiss>();
	VFX->SetPosition(Position);
	VFX->SetScale(m_Scale * 0.5f);
}

void Arrow::FireProjectile()
{
	// Get move direction
	float RadianAngle = GetTransform().Rotation * PI / 180;

	Vector2 MoveDirection = { cosf(RadianAngle), sinf(RadianAngle) };
	
	// Add force
	AddForce(MoveDirection, 30000.0f * m_Scale);
}
