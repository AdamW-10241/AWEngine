#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

#define Super Character

void Weapon::SetActive(bool State)
{
	// Update sprites
	for (Sprite* Sprites : GetAllSprites()) {
		Sprites->SetActive(State);
	}

	// Update bounds
	for (Bounds* Bounds : GetAllBounds()) {
		Bounds->m_Active = State;
	}

	m_Active = State;
}

void Weapon::Attack()
{
	if (!m_Active) {
		return;
	}
	
	if (m_CooldownTimer > 0.0f) {
		return;
	}

	OnAttack();

	m_AttackTimer = m_AttackDuration;
}

void Weapon::SetIdlePosition(float RadiusMultiplier)
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

void Weapon::SetAimPosition(float RadiusMultiplier)
{
	// Update object position
	Vector2 PlayerPosition = m_Owner->GetTransform().Position;

	SetPosition(PlayerPosition);

	// Update object sprite
	float RadianAngle = atan2(m_TargetPosition.y - PlayerPosition.y, m_TargetPosition.x - PlayerPosition.x);
	float Radius = m_Owner->ScaledHalfSize() * RadiusMultiplier;

	Vector2 OffsetPosition = { cosf(RadianAngle) * Radius, sinf(RadianAngle) * Radius };

	// Apply values to sprite
	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = (RadianAngle * 180 / PI) + m_RotationOffset;
	}
}

void Weapon::OnUpdate(float DeltaTime)
{
	if (!m_Active) {
		return;
	}
	
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
	if (!m_Active) {
		return;
	}
	
	if (IsCooldown()) {
		SetIdlePosition(m_RadiusMultiplier);
	}
	else if (IsAttacking()) {
		SetAttackPosition(m_RadiusMultiplier);
	}
	else {
		SetAimPosition(m_RadiusMultiplier);
	}

	Super::OnPostUpdate(DeltaTime);
}
