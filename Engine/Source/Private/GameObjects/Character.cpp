#include "GameObjects/Character.h"

#define Super PhysicsObject

Character::Character() : 
	m_MainSprite(nullptr),
	m_AccelerationSpeed(2000.0f),
	m_Scale(1.0f),
	m_Size(5.0f),
	m_Lives(1) {}

void Character::AddMovementInput(Vector2 Direction, float Scale)
{
	// Increase our movement direction based on a direction and scale
	m_MoveDirection += Direction.Normalise() * Scale;
}

int Character::ApplyDamage(GameObject* DamageCauser, int Damage)
{
	if (m_Lives <= 0 || IsPendingDestroy()) {
		return m_Lives;
	}

	m_Lives = std::max(0, m_Lives - Damage);

	if (m_Lives <= 0) {
		OnDeath(DamageCauser);
	}

	return m_Lives;
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
