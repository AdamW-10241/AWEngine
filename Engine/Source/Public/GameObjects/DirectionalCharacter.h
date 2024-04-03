#pragma once
#include "GameObjects/Character.h"

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

class DirectionalCharacter : public Character {
public:
	DirectionalCharacter() : m_LastMovementDirection(0) {}

	// Change the directional character sprite based on direction and idle state
	void SetAnimation(uint32_t Direction, bool IdleState);

	// Check and screen wrap the directional character
	void ScreenWrap(float HalfSpriteSize);

	// Check and screen border the directional character
	void ScreenBorder(float HalfSpriteSize);

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	// Store the different sprites
	TArray<Sprite*> m_DirectionSprites;

	// Store the last movement direction as integer
	// Right - 1, Left - 2, Up - 3, Down - 4
	uint32_t m_LastMovementDirection;
};