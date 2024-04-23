#include "GameObjects/Projectile.h"
#include "Math/Vector2.h"

#define Super Character

Projectile::Projectile()
{
	m_MaxSpeed = 1000.0f;
	m_AccelerationSpeed = 5000.0f;
	m_Drag = 0.0f;
	m_Deceleration = 0.0f;
	m_LifeTime = 1.0f;
	m_Dir = { 0.0f, -1.0f };
	m_Owner = nullptr;
	m_TargetTag = "ALL";
	m_Damage = 1;

	m_Size = 5.0f;

	m_Bounds = AddBounds(0.0f, ScaledSize());
}

void Projectile::FireProjectile(GameObject* Owner, Vector2 MoveDir, int OverrideDamage)
{
	if (Owner == nullptr) {
		return;
	}

	if (MoveDir != Vector2(0.0f)) {
		m_Dir = MoveDir;
	}

	if (OverrideDamage > 0) {
		m_Damage = OverrideDamage;
	}

	m_Owner = Owner;
}

void Projectile::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if (m_LifeTime > 0.0f) {
		m_LifeTime -= DeltaTime;
	}

	if (m_LifeTime <= 0.0f) {
		DestroyObject();
	}
	
	if (m_Owner == nullptr) {
		return;
	}

	AddMovementInput(m_Dir);
}

void Projectile::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	Super::OnOverlapEnter(OverlapBounds, HitBounds);

	if (m_Owner == nullptr) {
		return;
	}

	if (OverlapBounds->GetOwner() != m_Owner) {
		if (OverlapBounds->m_Tag == m_TargetTag) {
			if (auto Char = dynamic_cast<Character*>(OverlapBounds->GetOwner())) {
				Char->ApplyDamage(m_Owner, m_Damage);
			}
			DestroyObject();
		}
	}
}
