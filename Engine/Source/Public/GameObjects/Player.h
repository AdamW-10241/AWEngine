#pragma once
#include "GameObjects/Character.h"

class Player : public Character {
public:
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	// Change the player sprite based on direction and idle state
	void SetAnimation(uint32_t Direction, bool IdleState);

protected:
	// Store the different sprites for the player
	TArray<Sprite*> m_DirectionSprites;
};