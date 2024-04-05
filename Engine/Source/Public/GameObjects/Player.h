#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Projectile;

class Player : public DirectionalCharacter {
public:
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

	virtual void Cleanup() override;

	virtual void CollectGarbage() override;

private:
	void FireProjectile(Vector2 AimPosition);

private:
	// Store spawned projectiles
	TArray<Projectile*> m_Projectiles;

	// Delay between firing projectiles
	float m_FireDelay;

	// Flag to see if dead
	bool m_Dead;
};