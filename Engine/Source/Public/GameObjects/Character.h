#pragma once
#include "GameObjects/PhysicsObject.h"
#include "Math/Bounds.h"

class Character : public PhysicsObject {
public:
	Character();

	// Move the character in this direction based on the acceleration speed and max speed
	void AddMovementInput(Vector2 Direction, float Scale = 1.0f);

	// Get half of the size of the character
	float HalfSize() const { return m_Size / 2.0f; }

	// Get half the scaled size
	float ScaledHalfSize() const { return ScaledSize() / 2.0f; }

	// Get sized multiplied by the scale
	float ScaledSize() const { return m_Size * m_Scale; }

	// Reduce lives based on damage
	int ApplyDamage(GameObject* DamageCauser, int Damage);

	// Get the remaining lives of the character
	int GetLives() const { return m_Lives; }

public:
	// Dimensions of the character
	float m_Scale, m_Size;

protected:
	virtual void OnPostUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Main sprite that represents the character
	Sprite* m_MainSprite;

	// Speed the character will move to max speed
	float m_AccelerationSpeed;

	// The direction to move the character in
	Vector2 m_MoveDirection;

	// Lives of the character
	int m_Lives;
};