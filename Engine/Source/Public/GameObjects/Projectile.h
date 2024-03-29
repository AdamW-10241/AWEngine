#pragma once
#include "GameObjects/Character.h"

class Projectile : public Character {
public:
	Projectile(Vector2 AimPosition);

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

protected:
	// Store the different visual effects
	// TArray<Sprite*> m_VisualEffects;
};