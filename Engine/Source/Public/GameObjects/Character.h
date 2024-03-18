#pragma once
#include "GameObjects/PhysicsObject.h"
#include "Math/Bounds.h"

class Character : public PhysicsObject {
public:
	Character();

	// Move the character in this direction based on the acceleration speed and max speed
	void AddMovementInput(Vector2 Direction, float Scale = 1.0f);

protected:
	virtual void OnPostUpdate(float DeltaTime) override;

protected:
	// Main sprite that represents the character
	Sprite* m_MainSprite;

	// Speed the character will move to max speed
	float m_AccelerationSpeed;

	// The direction to move the character in
	Vector2 m_MoveDirection;
};