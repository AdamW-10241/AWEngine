#include "GameObjects/PhysicsObject.h"
#include "Input.h"

void PhysicsObject::OnStart()
{
	SetPosition({ 640.0f, 360.0f });
	SetScale({ 4.0f, 4.0f });
	
	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.MaxFrames = 12;
	AnimParams.EndFrame = 11;
	AnimParams.FrameWidth = 64;
	AnimParams.FrameHeight = 64;
	
	m_Sprite = AddSprite("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Round Shield.png",
		&AnimParams);
}

void PhysicsObject::OnProcessInput(Input* GameInput)
{
	// Find the Movement Direction
	m_MovementDirection = { 0.0f };

	if (GameInput->IsKeyDown(AW_KEY_W))
	{
		m_MovementDirection.y += -1.0f;
	}
	if (GameInput->IsKeyDown(AW_KEY_S))
	{
		m_MovementDirection.y += 1.0f;
	}
	if (GameInput->IsKeyDown(AW_KEY_A))
	{
		m_MovementDirection.x += -1.0f;
	}
	if (GameInput->IsKeyDown(AW_KEY_D))
	{
		m_MovementDirection.x += 1.0f;
	}
}

void PhysicsObject::OnUpdate(float DeltaTime)
{
	// Move the Object
	float speed = 400.0f * (float)DeltaTime;

	SetPosition(GetTransform().Position + m_MovementDirection * speed);

	// Update the Sprite
	if (m_Sprite != nullptr) {
		m_Sprite->Update(DeltaTime);
	}
}
