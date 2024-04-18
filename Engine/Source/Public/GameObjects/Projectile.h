#pragma once
#include "GameObjects/Character.h"

class Projectile : public Character {
public:
	Projectile();

	// Launch the projectile
	void FireProjectile(GameObject* Owner, Vector2 MoveDir = {0.0f}, int OverrideDamage = 0);

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

protected:
	// Time before projectile destroys itself
	float m_LifeTime;

	// Constant move direction
	Vector2 m_Dir;

	// Owner of the projectile
	GameObject* m_Owner;

	// Main projectile bounds
	Bounds* m_Bounds;

	// Target tag to hit
	const char* m_TargetTag;

	// Damage
	int m_Damage;
};