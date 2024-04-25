#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

#define Super Character

Weapon::Weapon(float DifficultyScale)
{
	// Set variables
	m_Owner = nullptr;
	m_Bounds = nullptr;
	m_TargetPosition = 0.0f;
	m_RotationOffset = 0.0f;
	m_RadiusMultiplier = 1.75f;
	m_Active = false;

	m_Damage = 1.0;
	m_Damage *= DifficultyScale;

	m_CooldownDuration = 1.0f;
	m_CooldownTimer = 0.0f;
	m_AttackDuration = 1.0f;
	m_AttackTimer = 0.0f;
}

void Weapon::SetOwner(DirectionalCharacter* Owner)
{
	// Set owner
	m_Owner = Owner;

	// Set target tag
	if (m_Bounds != nullptr) {
		m_Bounds->m_TargetTag = _strdup(Owner->GetMainBounds()->m_TargetTag);
	}
}

void Weapon::SetActive(bool State)
{
	// Set weapon state
	m_Active = State;
	
	// Update sprites
	for (Sprite* Sprites : GetAllSprites()) {
		Sprites->SetActive(State);
	}

	// Update bounds
	for (Bounds* Bounds : GetAllBounds()) {
		if (IsCooldown()) {
			Bounds->m_Active = false;
			continue;
		}
		
		Bounds->m_Active = State;
	}
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
