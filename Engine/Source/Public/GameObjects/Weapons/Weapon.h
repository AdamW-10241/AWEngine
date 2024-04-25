#pragma once
#include "GameObjects/Character.h"

class DirectionalCharacter;
class Bounds;

class Weapon : public Character {
public:
	Weapon() :
		m_Owner(nullptr),
		m_Bounds(nullptr),
		m_TargetPosition(0.0f),
		m_RotationOffset(0.0f),
		m_Damage(1.0f),
		m_CooldownDuration(1.0f), 
		m_CooldownTimer(0.0f),
		m_AttackDuration(1.0f), 
		m_AttackTimer(0.0f)
	{}

	void Attack();

	void SetOwner(DirectionalCharacter* Owner) { m_Owner = Owner; }

	bool IsAttacking() const { return m_AttackTimer > 0.0f; }

	virtual void SetAttackPosition() {}

	virtual void SetIdlePosition();

	virtual void SetAimPosition();

	void SetTargetPosition(Vector2 TargetPosition) { m_TargetPosition = TargetPosition; }

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnPostUpdate(float DeltaTime) override;

	virtual void OnAttack() {}

protected:
	// Store the owner reference
	DirectionalCharacter* m_Owner;

	// Store the weapon animations
	TArray<Sprite*> m_Animations;

	// Store the weapon bounds
	Bounds* m_Bounds;

	// Target position
	Vector2 m_TargetPosition;

	float m_RotationOffset;

	// Weapon stats
	float m_Damage;

	float m_CooldownDuration;

	float m_CooldownTimer;

	float m_AttackDuration;

	float m_AttackTimer;
};