#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

void Weapon::SetIdlePosition(DirectionalCharacter* OwnerRef)
{
	SetPosition(OwnerRef->GetTransform().Position);

	Vector2 SideOffset = OwnerRef->GetLastMovementDirection() * OwnerRef->ScaledHalfSize() * 1.75f;

	// make rotation change based on the angle from get last movement direction

	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = SideOffset;
		WeaponSprite->m_Offset.Rotation = 90;
	}
}

void Weapon::OnUpdate(float DeltaTime)
{
	if (m_AnimationTimer > 0.0f) {
		m_AnimationTimer -= DeltaTime;
	}
}

void Weapon::OnAttack()
{
	if (IsPendingDestroy()) {
		return;
	}

	m_AnimationTimer = m_AnimationDuration;
}
