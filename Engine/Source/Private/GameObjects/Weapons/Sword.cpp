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

	m_Scale = 4.0f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Weapons/Sword2/Sprite.png"
	);

	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	float const BoundsScalar = 4.0f;

	m_Bounds = AddBounds(0.0f, ScaledSize() * BoundsScalar);
	m_Bounds->m_OriginOffset = -ScaledHalfSize() * BoundsScalar;
	m_Bounds->m_Tag = "WEAPON";
	m_Bounds->m_Debug = true;
}

void Sword::SetAnimationPosition(DirectionalCharacter* OwnerRef)
{
	SetPosition(OwnerRef->GetTransform().Position);
	
	float Radius = OwnerRef->ScaledHalfSize() * 1.75f;
	float AngleRatio = m_AnimationTimer / m_AnimationDuration;

	Vector2 OffsetPosition = { cosf(2 * PI * AngleRatio) * Radius, sinf(2 * PI * AngleRatio) * Radius };

	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = 360 * AngleRatio;

		// fix rotation angle
	}
}

void Sword::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (IsPendingDestroy()) {
		return;
	}
}