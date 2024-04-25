#pragma once
#include "GameObjects/Character.h"

class DirectionalCharacter;

class Projectile : public Character {
public:
	Projectile();

	// Set projectile owner
	void SetupProjectile(DirectionalCharacter* Owner, int Damage);

	// Set damage
	void SetDamage(int Damage) { m_Damage = Damage; }

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

	virtual void CreateVFX(DirectionalCharacter* Owner) {}

	virtual void FireProjectile() {}

protected:
	// Main projectile bounds
	Bounds* m_Bounds;

	// Constant move direction
	Vector2 m_MoveDirection;

	// Owner of the projectile
	DirectionalCharacter* m_Owner;

	// Target tag to hit
	const char* m_TargetTag;

	// Time before projectile destroys itself
	float m_LifeTime;

	// Damage
	int m_Damage;
};