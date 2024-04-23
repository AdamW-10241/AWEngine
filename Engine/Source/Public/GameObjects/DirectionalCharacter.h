#pragma once
#include "GameObjects/Character.h"
#include "GameObjects/Weapons/Weapon.h"

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

class DirectionalCharacter : public Character {
public:
	DirectionalCharacter() {
		m_LastMovementDirection = 0;
		m_BaseRateOfAttack = 1.0f;
		m_RateOfAttack = m_BaseRateOfAttack;
		m_AttackTimer = 0.0f;
	}

	// Change the directional character sprite based on direction and idle state
	void SetAnimation(uint32_t Direction, bool IdleState);

	// Check and screen wrap the directional character
	void ScreenWrap(float HalfSpriteSize);

	// Check and screen border the directional character
	void ScreenBorder(float HalfSpriteSize);

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void Cleanup() override;

	virtual void OnDeath(GameObject* DeathCauser) override;

	void AddWeapon(Weapon* NewWeapon) { m_OwnedWeapons.push_back(NewWeapon); }

	void Attack();

protected:
	// Store the different sprites
	TArray<Sprite*> m_DirectionSprites;

	// Store the different weapons'
	TArray<Weapon*> m_OwnedWeapons;

	// Store the last movement direction as integer
	// Right - 1, Left - 2, Up - 3, Down - 4
	uint32_t m_LastMovementDirection;

	// Timer values for firing projectiles
	float m_BaseRateOfAttack, m_RateOfAttack, m_AttackTimer;
};