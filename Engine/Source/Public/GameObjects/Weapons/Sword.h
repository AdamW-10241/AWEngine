#pragma once
#include "GameObjects/Weapons/Weapon.h"

class Sword : public Weapon {
public:
	Sword(float DifficultyScale = 1.0f);

	virtual void SetAnimationPosition(DirectionalCharacter* OwnerRef) override;

protected:
	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
};