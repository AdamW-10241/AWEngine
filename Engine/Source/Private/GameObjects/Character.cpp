#include "GameObjects/Character.h"

#define Super PhysicsObject

Character::Character() : m_MainSprite(nullptr), m_AccelerationSpeed(2000.0f) {}

void Character::AddMovementInput(Vector2 Direction, float Scale)
{
	// Increase our movement direction based on a direction and scale
	m_MoveDirection += Direction.Normalise() * Scale;
}

void Character::OnPostUpdate(float DeltaTime)
{
	// If we have a movement direction set, move the object using physics
	if (m_MoveDirection.Length() > 0.0f) {
		AddForce(m_MoveDirection, m_AccelerationSpeed);
	}

	// Reset move direction for the next frame
	m_MoveDirection = Vector2();
	
	Super::OnPostUpdate(DeltaTime);
}
