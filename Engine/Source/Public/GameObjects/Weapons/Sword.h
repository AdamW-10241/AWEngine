#pragma once
#include "GameObjects/Weapons/Weapon.h"

class Sword : public Weapon {
public:
	Sword(float DifficultyScale = 1.0f);

	virtual void SetAttackPosition(float RadiusMultiplier = 1.0f) override;

	virtual void SetAimPosition(float RadiusMultiplier = 1.0f) override;

protected:
	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

	virtual void OnAttack() override;
};