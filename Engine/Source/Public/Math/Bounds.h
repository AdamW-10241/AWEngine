#pragma once
#include "Math/Vector2.h"
#include <cstdint>
#include "EngineTypes.h"

class GameObject;

struct AWRect {
	// Default constructor
	AWRect() : Origin(0.0f), Extent(1.0f) {}

	// Complex constructor 
	AWRect(Vector2 Origin, Vector2 Extent) :
		Origin(Origin), Extent(Extent) {}

	// Min value position of the box relative to the screen
	Vector2 Min() const { return Origin - Extent; }

	// Max value position of the box relative to the screen
	Vector2 Max() const { return Origin + Extent; }

	// Center of the box
	Vector2 Origin;

	// Half size of the box
	Vector2 Extent;
};

enum AWCollisionType : unsigned int {
	CT_NONE = 0,
	CT_OVERLAP
};

struct STBoundsColour {
	// Default constructor
	STBoundsColour() : r(255), g(0), b(0) {}

	// Complex constructor
	STBoundsColour(uint8_t r, uint8_t g, uint8_t b) :
		r(r), g(g), b(b) {}

	uint8_t r;
	uint8_t g;
	uint8_t b;
};

class Bounds {
public:
	Bounds(GameObject* Owner, Vector2 Origin = 0.0f, Vector2 Extent = 1.0f);

	// The center equals the origin + the offset
	Vector2 GetCenter() const { return m_Rect.Origin + m_OriginOffset; }

	// Detect if two bounds are intersecting
	static bool BoundsIntersect(const Bounds& BoundsA, const Bounds& BoundsB);

	// Get the game object that owns the bounds
	GameObject* GetOwner() const { return m_Owner; }

	// Mark the bounds for destroy
	void DestroyBounds() { m_ShouldDestroy = true; }

	// Check if the bounds is marked for destroy
	bool isPendingDestroy() const { return m_ShouldDestroy; }

	// Resize the bounds
	void SetBoundsExtent(Vector2 Extent);

public:
	// The rectangle that defines the bounds
	AWRect m_Rect;

	// The offset from the original position
	Vector2 m_OriginOffset;

	// Collision type
	AWCollisionType m_CollisionType;

	// Name of the collision
	const char* m_Tag;

	// Colour of the bounds if debug is active
	STBoundsColour m_RenderColour;

	// All currently overlapping bounds
	TArray<Bounds*> m_Overlapped;

	// Debug visualise bounds
	bool m_Debug;

private:
	// The owner object the bounds is attached to
	GameObject* m_Owner;
	
	// Flag that says whether the bounds should be marked for destroy
	bool m_ShouldDestroy;
};