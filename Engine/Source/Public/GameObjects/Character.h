#pragma once
#include "GameObjects/PhysicsObject.h"
#include "Math/Bounds.h"

#define PI 3.1415926f

class Character : public PhysicsObject {
public:
	Character() :
		m_MainSprite(nullptr),
		m_AccelerationSpeed(2000.0f),
		m_Scale(1.0f),
		m_Size(5.0f),
		m_MaxHealth(1.0f),
		m_Health(1.0f),
		m_Bounds(nullptr) 
	{}

	// Move the character in this direction based on the acceleration speed and max speed
	void AddMovementInput(Vector2 Direction, float Scale = 1.0f);

	// Get half of the size of the character
	float HalfSize() const { return m_Size / 2.0f; }

	// Get half the scaled size
	float ScaledHalfSize() const { return ScaledSize() / 2.0f; }

	// Get sized multiplied by the scale
	float ScaledSize() const { return m_Size * m_Scale; }

	// Reduce health based on damage
	float ApplyDamage(GameObject* DamageCauser, float Damage);

	// Get the remaining health of the character
	float GetHealth() const { return m_Health; }

	// Reset health to max health
	void ResetHealth() { m_Health = m_MaxHealth; }

	// Get main bounds
	Bounds* GetMainBounds() const { return m_Bounds; }

public:
	// Dimensions of the character
	float m_Scale, m_Size;

protected:
	virtual void OnPostUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Main sprite that represents the character
	Sprite* m_MainSprite;

	// Main bounds
	Bounds* m_Bounds;

	// Speed the character will move to max speed
	float m_AccelerationSpeed;

	// The direction to move the character in
	Vector2 m_MoveDirection;

	// Health of the character
	float m_MaxHealth, m_Health;
};