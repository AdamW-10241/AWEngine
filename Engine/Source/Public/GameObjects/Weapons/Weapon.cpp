#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

#define Super Character

void Weapon::Attack()
{
	if (m_CooldownTimer > 0.0f) {
		return;
	}

	OnAttack();

	m_AttackTimer = m_AttackDuration;
}

void Weapon::SetIdlePosition()
{
	// Update object position
	Vector2 PlayerPosition = m_Owner->GetTransform().Position;

	SetPosition(PlayerPosition);

	// Update object sprite
	float Radius = m_Owner->ScaledHalfSize();

	Vector2 OffsetPosition = m_Owner->GetLastMovementDirection() * Radius;

	// Apply values to sprite
	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = 0;
	}
}

void Weapon::SetAimPosition()
{
	// Update object position
	Vector2 PlayerPosition = m_Owner->GetTransform().Position;

	SetPosition(PlayerPosition);

	// Update object sprite
	float RadianAngle = atan2(m_TargetPosition.y - PlayerPosition.y, m_TargetPosition.x - PlayerPosition.x);
	float Radius = m_Owner->ScaledHalfSize() * 1.75f;

	Vector2 OffsetPosition = { cosf(RadianAngle) * Radius, sinf(RadianAngle) * Radius };

	// Apply values to sprite
	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = (RadianAngle * 180 / PI) + m_RotationOffset;
	}
}

void Weapon::OnUpdate(float DeltaTime)
{
	if (m_AttackTimer > 0.0f) {
		m_AttackTimer -= DeltaTime;
	}

	if (m_CooldownTimer > 0.0f) {
		m_CooldownTimer -= DeltaTime;
	}

	Super::OnUpdate(DeltaTime);
}

void Weapon::OnPostUpdate(float DeltaTime)
{
	if (m_CooldownTimer > 0.0f) {
		SetIdlePosition();
	}
	else if (IsAttacking()) {
		SetAttackPosition();
	}
	else {
		SetAimPosition();
	}

	Super::OnPostUpdate(DeltaTime);
}
