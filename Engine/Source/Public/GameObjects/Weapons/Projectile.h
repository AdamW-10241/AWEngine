#pragma once
#include "GameObjects/Character.h"

class Weapon;

class Projectile : public Character {
public:
	Projectile();

	// Set projectile owner
	void SetupProjectile(Weapon* Owner, float Damage);

	// Set damage
	void SetDamage(int Damage) { m_Damage = Damage; }

	// Get owner
	Weapon* GetOwner() const { return m_Owner; }

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

	virtual void CreateHitVFX(Vector2 Position) {}

	virtual void CreateMissVFX(Vector2 Position) {}

	virtual void FireProjectile() {}

	virtual void AttackHit(Character* Char, bool DoDamage);

	virtual void AttackMiss();

protected:
	// Main projectile bounds
	Bounds* m_Bounds;

	// Constant move direction
	Vector2 m_MoveDirection;

	// Owner of the projectile
	Weapon* m_Owner;

	// Time before projectile destroys itself
	float m_LifeTime;

	// Damage
	float m_Damage;
};