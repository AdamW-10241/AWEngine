#include "GameObjects/Weapons/Sword.h"
#include "GameObjects/DirectionalCharacter.h"

#include "Debug.h"

#define Super Weapon

Sword::Sword(float DifficultyScale)
{
	// Set variables
	m_Damage = 1.0f;
	m_Damage *= DifficultyScale;

	m_CooldownDuration = 1.5f;
	m_AttackDuration = 0.3f;

	m_RotationOffset = 90.0f;

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

void Sword::SetAttackPosition()
{
	// Update object position
	Vector2 PlayerPosition = m_Owner->GetTransform().Position;

	SetPosition(PlayerPosition);

	// Update object sprite
	float AngleRatio = 2 * PI * m_AttackTimer / m_AttackDuration;

	Vector2 TargetPosition = PlayerPosition + Vector2(cosf(AngleRatio), sinf(AngleRatio));

	float RadianAngle = atan2(TargetPosition.y - PlayerPosition.y, TargetPosition.x - PlayerPosition.x);
	float Radius = m_Owner->ScaledHalfSize() * 1.75f;

	Vector2 OffsetPosition = { cosf(RadianAngle) * Radius, sinf(RadianAngle) * Radius };

	// Apply values to sprite
	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = (RadianAngle * 180 / PI) + m_RotationOffset;
	}
}

void Sword::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (!IsAttacking()) {
		return;
	}

	if (OverlapBounds->GetOwner() != m_Owner) {
		if (auto Char = dynamic_cast<DirectionalCharacter*>(OverlapBounds->GetOwner())) {
			Char->ApplyDamage(m_Owner, m_Damage);
			m_CooldownTimer = m_CooldownDuration;
		}
	}
}