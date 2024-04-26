#include "GameObjects/Character.h"

#define Super PhysicsObject

void Character::AddMovementInput(Vector2 Direction, float Scale)
{
	// Increase our movement direction based on a direction and scale
	m_MoveDirection += Direction.Normalise() * Scale;
}

float Character::ApplyDamage(GameObject* DamageCauser, float Damage)
{
	if (m_Health <= 0 || IsPendingDestroy()) {
		return m_Health;
	}

	m_Health = std::fmax(0.0f, m_Health - Damage);

	if (m_Health <= 0) {
		OnDeath(DamageCauser);
	}

	return m_Health;
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

void Character::OnDeath(GameObject* DeathCauser)
{
	DestroyObject();
}
