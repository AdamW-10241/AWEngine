#include "GameObjects/GameObject.h"
#include "Math/Bounds.h"
#include "Debug.h"

void GameObject::Start()
{
	if (IsPendingDestroy()) {
		return;
	}

	AW_LOG("Game Object", "GameObject has spawned into the game.");

	OnStart();

	BoundsMatchObjectPosition();
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

void GameObject::Cleanup()
{
	for (auto TestBounds : m_BoundsStack) {
		delete TestBounds;
	}
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

	// Move any bounds to the same position as the object
	BoundsMatchObjectPosition();
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

void GameObject::TestOverLapEvent(Bounds* OtherBounds)
{
	// Make sure the other bounds is set to detect collisions
	if (OtherBounds->m_CollisionType == CT_NONE) {
		return;
	}

	for (auto TestBounds : m_BoundsStack) {
		// Make sure the objects bounds are set to detect collisions
		if (TestBounds->m_CollisionType == CT_NONE) {
			continue;
		}

		// This makes sure that the bounds is not from this object
		if (OtherBounds->GetOwner() == this) {
			continue;
		}

		// Search through the overlapped array to detect if we've already overlapped
		auto it = std::find(
			TestBounds->m_Overlapped.begin(),
			TestBounds->m_Overlapped.end(),
			OtherBounds
		);
		// Detect if bounds are intersecting
		bool IsIntersecting = Bounds::BoundsIntersect(*TestBounds, *OtherBounds);
		// Is the bounds already overlapped
		bool IsOverlapped = it != TestBounds->m_Overlapped.end();

		if (IsOverlapped) {
			if (!IsIntersecting) {
				// Removes the other bounds from the overlapped array
				TestBounds->m_Overlapped.erase(it);
				// Run the exit function
				OnOverlapExit(OtherBounds, TestBounds);

				AW_LOG("GameObject", "Exit Intersection.");
			}
		}
		else {
			if (IsIntersecting) {
				// Add the other bounds to the overlap array
				TestBounds->m_Overlapped.push_back(OtherBounds);
				// Run the enter function
				OnOverlapEnter(OtherBounds, TestBounds);

				AW_LOG("GameObject", "Enter Intersection.");
			}
		}

		// Change the colour if there is anything overlapping this bounds
		// and set the overlapping flag
		if (TestBounds->m_Overlapped.size() > 0) {
			// Green
			TestBounds->m_RenderColour = STBoundsColour(0, 255, 0);
			m_IsOverlapping = true;
		}
		else {
			// Red
			TestBounds->m_RenderColour = STBoundsColour(255, 0, 0);
			m_IsOverlapping = false;
		}
	}
}

void GameObject::OnDestroy()
{
	AW_LOG("Game Object", "GameObject has been destroyed.");
}

Bounds* GameObject::AddBounds(Vector2 Center, Vector2 Extent)
{
	Bounds* NewBounds = new Bounds(this, Center, Extent);
	m_BoundsStack.push_back(NewBounds);
	
	return NewBounds;
}

void GameObject::BoundsMatchObjectPosition()
{
	// Move any bounds to the same position as the object
	for (auto TestBounds : m_BoundsStack) {
		if (TestBounds == nullptr) {
			continue;
		}

		TestBounds->m_Rect.Origin = GetTransform().Position;
	}
}
