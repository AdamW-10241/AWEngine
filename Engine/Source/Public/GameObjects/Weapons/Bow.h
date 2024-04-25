#pragma once
#include "GameObjects/Weapons/Weapon.h"

class Bow : public Weapon {
public:
	Bow(float DifficultyScale = 1.0f);

protected:
	virtual void OnAttack() override;

	virtual void SetIdlePosition(float RadiusMultiplier = 1.0f) override;

	void SpawnArrow();

protected:
	uint32_t m_Arrows;
};