#pragma once
#include "GameObjects/Character.h"
#include "GameObjects/Weapons/Weapon.h"

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

class DirectionalCharacter : public Character {
public:
	DirectionalCharacter() : m_LastMovementDirection(0), m_UsedWeapon(0) {}

	// Change the directional character sprite based on direction and idle state
	void SetAnimation(uint32_t Direction, bool IdleState);

	// Check and screen wrap the directional character
	void ScreenWrap(float HalfSpriteSize);

	// Check and screen border the directional character
	void ScreenBorder(float HalfSpriteSize);

	// Get last movement direction vector
	Vector2 GetLastMovementDirection();

	// Update weapon state
	void UpdateWeaponStates();

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void Cleanup() override;

	virtual void CollectGarbage() override;

	virtual void OnDeath(GameObject* DeathCauser) override;

	void AddWeapon(Weapon* NewWeapon);

	void DestroyWeapons();

	void Attack(Vector2 TargetPosition, bool AttackCondition);

protected:
	// Store the different sprites
	TArray<Sprite*> m_DirectionSprites;

	// Store the different weapons
	TArray<Weapon*> m_OwnedWeapons;

	// Store the index of the used weapon
	uint32_t m_UsedWeapon;

	// Store the last movement direction as integer
	// Right - 1, Left - 2, Up - 3, Down - 4
	uint32_t m_LastMovementDirection;
};