#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Enemy : public DirectionalCharacter {
public:
	Enemy();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	// Time until the next movemnt choice is made
	float m_TimeUntilNextMovementChoice;

	// Movement made by the enemy until the next movement choice
	Vector2 m_MovementChoice;
};