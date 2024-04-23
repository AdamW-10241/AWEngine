#include "GameObjects/DirectionalCharacter.h"

#define Super Character

void DirectionalCharacter::OnProcessInput(Input* GameInput)
{
	Super::OnProcessInput(GameInput);
}

void DirectionalCharacter::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Get the directional character idle state
	// idle = true, moving = false
	bool IdleState = (m_MoveDirection.Length() <= 0.0f);

	// Update the last movement direction
	if (m_MoveDirection.x > 0) {
		m_LastMovementDirection = DIRECTION_RIGHT;
	}
	else if (m_MoveDirection.x < 0) {
		m_LastMovementDirection = DIRECTION_LEFT;
	}
	else if (m_MoveDirection.y < 0) {
		m_LastMovementDirection = DIRECTION_UP;
	}
	else if (m_MoveDirection.y > 0) {
		m_LastMovementDirection = DIRECTION_DOWN;
	}

	// Set the directional character animations
	SetAnimation(m_LastMovementDirection, IdleState);
}

void DirectionalCharacter::SetAnimation(uint32_t Direction, bool IdleState)
{
	// Check all sprites are not nullptr
	if (m_DirectionSprites.size() > 7) {
		for (int Sprite = 0; Sprite < 8; Sprite++) {
			if (m_DirectionSprites[Sprite] == nullptr) {
				return;
			}
		}
	}

	// Set all direction sprites (idle and moving) to inactive
	for (int Sprite = 0; Sprite < 8; Sprite++) {
		m_DirectionSprites[Sprite]->SetActive(false);
	}

	// Activate the correct direction sprite (idle and moving)
	// + 4 when the idle state is false (moving) to get the latter moving sprites
	m_DirectionSprites[Direction + !IdleState * 4]->SetActive(true);
}

void DirectionalCharacter::ScreenWrap(float HalfSpriteSize)
{
	// Screen wrap the directional character
	// Bottom to top
	if (GetTransform().Position.y - HalfSpriteSize > 720) {
		SetPosition({ GetTransform().Position.x, -HalfSpriteSize });
	}
	// Top to bottom
	if (GetTransform().Position.y + HalfSpriteSize < -HalfSpriteSize) {
		SetPosition({ GetTransform().Position.x, 720 + HalfSpriteSize });
	}
	// Right to left
	if (GetTransform().Position.x - HalfSpriteSize > 1280) {
		SetPosition({ -HalfSpriteSize, GetTransform().Position.y });
	}
	// Left to right
	if (GetTransform().Position.x + HalfSpriteSize < -HalfSpriteSize) {
		SetPosition({ 1280 + HalfSpriteSize, GetTransform().Position.y });
	}
}

void DirectionalCharacter::ScreenBorder(float HalfSpriteSize)
{
	// Screen border the directional character
	// Bottom to top
	if (GetTransform().Position.y + HalfSpriteSize > 720) {
		SetPosition({ GetTransform().Position.x, 720 - HalfSpriteSize });
	}
	// Top to bottom
	if (GetTransform().Position.y - HalfSpriteSize < 0) {
		SetPosition({ GetTransform().Position.x, HalfSpriteSize });
	}
	// Right to left
	if (GetTransform().Position.x + HalfSpriteSize > 1280) {
		SetPosition({ 1280 - HalfSpriteSize, GetTransform().Position.y });
	}
	// Left to right
	if (GetTransform().Position.x - HalfSpriteSize < 0) {
		SetPosition({ HalfSpriteSize, GetTransform().Position.y });
	}
}