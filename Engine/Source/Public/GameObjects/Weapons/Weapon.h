#pragma once
#include "GameObjects/Character.h"

class Weapon : public Character {
public:
	Weapon() : m_Damage(1.0f), m_AttackCooldown(1.0f) {}

	void Attack() { OnAttack(); }

protected:
	virtual void OnAttack() {}

protected:
	// Store the weapon animations
	TArray<Sprite*> m_Animations;

	float m_Damage;

	float m_AttackCooldown;
};