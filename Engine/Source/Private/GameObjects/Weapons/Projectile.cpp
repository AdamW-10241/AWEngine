#include "GameObjects/Weapons/Projectile.h"
#include "GameObjects/DirectionalCharacter.h"

#include "Math/Vector2.h"

#define Super Character

Projectile::Projectile()
{
	// Set variables
	m_MaxSpeed = 1000.0f;
	m_AccelerationSpeed = 1000.0f;
	m_Drag = 0.0f;
	m_Deceleration = 0.0f;

	m_LifeTime = 1.0f;
	m_Owner = nullptr;
	m_Size = 5.0f;

	m_TargetTag = "NONE";
	m_Damage = 1;

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
}

void Projectile::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if (m_LifeTime > 0.0f) {
		m_LifeTime -= DeltaTime;
	}

	if (m_LifeTime <= 0.0f) {
		// Create Miss VFX
		CreateMissVFX(GetTransform().Position);

		DestroyObject();
	}
	
	if (m_Owner == nullptr) {
		return;
	}

	AddMovementInput(m_MoveDirection);
}

void Projectile::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->GetOwner() != m_Owner || OverlapBounds->m_Tag == HitBounds->m_TargetTag) {
		if (auto Char = dynamic_cast<DirectionalCharacter*>(OverlapBounds->GetOwner())) {
			// Damage opponent
			Char->ApplyDamage(m_Owner, m_Damage);

			// Create Hit VFX
			CreateHitVFX(Char->GetTransform().Position);

			// Delete projectile
			DestroyObject();
		}
	}
}

void Projectile::SetupProjectile(DirectionalCharacter* Owner, int Damage)
{
	// Set owner
	m_Owner = Owner;

	// Copy target tag
	if (m_Owner->GetAllBounds().size() > 0) {
		m_Bounds->m_TargetTag = _strdup(Owner->GetAllBounds().at(0)->m_TargetTag);
	}

	// Set damage
	m_Damage = Damage;
}
