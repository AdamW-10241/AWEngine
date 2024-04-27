#include "GameObjects/Weapons/Projectile.h"
#include "GameObjects/Weapons/Weapon.h"
#include "GameObjects/DirectionalCharacter.h"

#include "SDL2/SDL_mixer.h"
#include "Math/Vector2.h"

#include "Debug.h"

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

	m_Damage = 1.0f;

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_Tag = "PROJECTILE";

	// Toggle
	m_ToggleSprite = false;
}

void Projectile::ToggleSprite()
{
	// Toggle sprite
	m_ToggleSprite = !m_ToggleSprite;
}

void Projectile::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if (m_LifeTime > 0.0f) {
		m_LifeTime -= DeltaTime;
	}

	if (m_LifeTime <= 0.0f) {
		AttackMiss();
	}
	
	if (m_Owner == nullptr) {
		return;
	}

	AddMovementInput(m_MoveDirection);
}

void Projectile::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->GetOwner() == m_Owner) {
		return;
	}

	// Hit player / enemy
	if (auto const Char = dynamic_cast<DirectionalCharacter*>(OverlapBounds->GetOwner())) {
		if (strcmp(Char->GetMainBounds()->m_Tag, HitBounds->m_TargetTag) != 0) {
			return;
		}

		// Do attack hit
		AttackHit(Char, true);

		return;
	}

	// Hit weapon
	if (auto const OtherWeapon = dynamic_cast<Weapon*>(OverlapBounds->GetOwner())) {
		if (strcmp(OtherWeapon->GetOwner()->GetMainBounds()->m_Tag, HitBounds->m_TargetTag) != 0) {
			return;
		}
		
		// Make other weapon attack land
		OtherWeapon->AttackHit(this, false);

		// Do attack hit
		AttackHit(OtherWeapon, false);
		return;
	}

	// Hit projectile
	if (auto const OtherProjectile = dynamic_cast<Projectile*>(OverlapBounds->GetOwner())) {
		if (strcmp(OtherProjectile->GetOwner()->GetOwner()->GetMainBounds()->m_Tag, HitBounds->m_TargetTag) != 0) {
			return;
		}

		// Make other projectile attack land
		OtherProjectile->AttackHit(this, false);

		// Do attack hit
		AttackHit(OtherProjectile, false);
		return;
	}
}

void Projectile::AttackHit(Character* Char, bool DoDamage)
{
	// Damage opponent if set
	if (DoDamage) {
		Char->ApplyDamage(m_Owner, m_Damage);
	}
	
	// Create hit VFX
	CreateHitVFX((Char->GetTransform().Position + GetTransform().Position) / 2.0f);

	// Play hit SFX
	if (m_Owner->GetSFX(W_SFX_HIT) != nullptr) {
		Mix_PlayChannel(-1, m_Owner->GetSFX(W_SFX_HIT), 0);
	}

	// Destroy projectile
	DestroyObject();
}

void Projectile::AttackMiss()
{
	// Create miss VFX
	CreateMissVFX(GetTransform().Position);

	// Play miss SFX
	if (m_P_SFX[W_SFX_MISS] != nullptr) {
		Mix_PlayChannel(-1, m_P_SFX[W_SFX_MISS], 0);
	}

	// Destroy projectile
	DestroyObject();
}

void Projectile::SetupProjectile(Weapon* Owner, float Damage)
{
	// Set owner
	m_Owner = Owner;

	// Copy target tag
	if (m_Bounds != nullptr) {
		m_Bounds->m_TargetTag = _strdup(Owner->GetOwner()->GetMainBounds()->m_TargetTag);
	}

	// Set damage
	m_Damage = Damage;

	// Copy sounds
	for (int Sound = 0; Sound < W_SFX::W_SFX_NUM; Sound++) {
		m_P_SFX[Sound] = Owner->GetSFX((W_SFX)Sound);
	}
}
