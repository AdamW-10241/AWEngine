#pragma once
#include "GameObjects/Character.h"

class DirectionalCharacter;
class Bounds;

class Weapon : public Character {
public:
	Weapon() : m_Damage(1.0f), m_AnimationCooldown(1.0f), m_AnimationDuration(1.0f), m_AnimationTimer(0.0f) {}

	void Attack() { OnAttack(); }

	bool IsAnimating() const { return m_AnimationTimer > 0.0f; }

	virtual void SetAnimationPosition(DirectionalCharacter* OwnerRef) {}

	virtual void SetIdlePosition(DirectionalCharacter* OwnerRef);

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnAttack();

protected:
	// Store the weapon animations
	TArray<Sprite*> m_Animations;

	// Store the weapon bounds
	Bounds* m_Bounds;

	// Weapon stats
	float m_Damage;

	float m_AnimationCooldown;

	float m_AnimationDuration;

	float m_AnimationTimer;
};