#include "GameObjects/GameObject.h"
#include "Debug.h"

void GameObject::Start()
{
	if (IsPendingDestroy()) {
		return;
	}

	AW_LOG("Game Object", "GameObject has spawned into the game.");

	OnStart();
}

void GameObject::ProcessInput(Input* GameInput)
{
	if (IsPendingDestroy()) {
		return;
	}

	OnProcessInput(GameInput);
}

void GameObject::Update(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}

	OnUpdate(DeltaTime);
}

void GameObject::PostUpdate(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}

	OnPostUpdate(DeltaTime);
}

void GameObject::DestroyObject()
{
	// Ensure the OnDestroy only runs once
	if (!m_ShouldDestroy) {
		OnDestroy();
	}

	m_ShouldDestroy = true;
}

void GameObject::SetTransform(AWTransform Transform)
{
	m_Transform = Transform;
}

void GameObject::SetPosition(Vector2 Position)
{
	AWTransform NewTransform(
		Position,
		m_Transform.Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetRotation(float Rotation)
{
	AWTransform NewTransform(
		m_Transform.Position,
		Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetScale(Vector2 Scale)
{
	AWTransform NewTransform(
		m_Transform.Position,
		m_Transform.Rotation,
		Scale
	);

	SetTransform(NewTransform);
}

void GameObject::OnDestroy()
{
	AW_LOG("Game Object", "GameObject has been destroyed.");
}