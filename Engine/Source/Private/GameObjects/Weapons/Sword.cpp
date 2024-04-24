#include "GameObjects/Weapons/Sword.h"
#include "GameObjects/DirectionalCharacter.h"

#include "Debug.h"

#define Super Weapon

Sword::Sword(float DifficultyScale)
{
	// Set variables
	m_Damage = 1.0f;
	m_Damage *= DifficultyScale;

	m_AnimationDuration = 0.35f;

	m_Scale = 3.0f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Weapons/Sword2/Sprite.png"
	);

	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Tag = "WEAPON";
	m_Bounds->m_Debug = true;
}

void Sword::SetAnimationPosition(DirectionalCharacter* OwnerRef)
{
	float Radius = OwnerRef->ScaledHalfSize() * 1.75f;
	float Angle = 2 * PI * (m_AnimationTimer / m_AnimationDuration);

	Vector2 OffsetPosition = { cosf(Angle) * Radius, sinf(Angle) * Radius };

	SetPosition(OwnerRef->GetTransform().Position + OffsetPosition);

	m_Bounds->SetBoundsExtent({ ScaledSize() + cosf(Angle) * ScaledSize(), ScaledSize() + sinf(Angle) * ScaledSize() });
}

void Sword::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (IsPendingDestroy()) {
		return;
	}
}