#pragma once
#include "GameObjects/Weapons/Weapon.h"

class Bow : public Weapon {
public:
	Bow(float DifficultyScale = 1.0f);

	// Toggles
	void ToggleTripleShot() { m_ToggleTripleShot = !m_ToggleTripleShot; }

protected:
	virtual void OnAttack() override;

	virtual void SetIdlePosition(float RadiusMultiplier = 1.0f) override;

	void SpawnArrow(float rotationOffset = 0.0f);

protected:
	uint32_t m_Arrows;

	// Toggle
	bool m_ToggleTripleShot;
};