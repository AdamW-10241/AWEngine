#pragma once
#include "GameObjects/Character.h"

class DirectionalCharacter;
class Bounds;

class Weapon : public Character {
public:
	Weapon(float DifficultyScale = 1.0f);

	void SetOwner(DirectionalCharacter* Owner) { m_Owner = Owner; }

	void SetTargetPosition(Vector2 TargetPosition) { m_TargetPosition = TargetPosition; }

	void SetActive(bool State);
	
	void Attack();

	bool IsAttacking() const { return m_AttackTimer > 0.0f; }

	bool IsCooldown() const { return m_CooldownTimer > 0.0; }

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnPostUpdate(float DeltaTime) override;

	virtual void OnAttack() {}

	virtual void SetIdlePosition(float RadiusMultiplier = 1.0f);

	virtual void SetAimPosition(float RadiusMultiplier = 1.0f);

	virtual void SetAttackPosition(float RadiusMultiplier = 1.0f) { SetAimPosition(m_RadiusMultiplier); }

protected:
	// Store the owner reference
	DirectionalCharacter* m_Owner;

	// Store the weapon animations
	TArray<Sprite*> m_Animations;

	// Store the weapon bounds
	Bounds* m_Bounds;

	// Positional values
	Vector2 m_TargetPosition;

	float m_RotationOffset;

	float m_RadiusMultiplier;

	// Weapon state
	bool m_Active;

	// Weapon stats
	float m_Damage;

	float m_CooldownDuration;

	float m_CooldownTimer;

	float m_AttackDuration;

	float m_AttackTimer;
};