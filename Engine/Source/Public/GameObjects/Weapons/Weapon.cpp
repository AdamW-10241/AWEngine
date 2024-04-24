#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

void Weapon::SetIdlePosition(DirectionalCharacter* OwnerRef)
{
	Vector2 SideOffset = OwnerRef->GetLastMovementDirection() * OwnerRef->ScaledHalfSize() * 1.75f;

	SetPosition(OwnerRef->GetTransform().Position + SideOffset);
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
