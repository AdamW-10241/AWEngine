#pragma once
#include "Math/Vector2.h"	
#include "EngineTypes.h"

class Input;
class Bounds;

struct AWTransform {
	// Default constructor
	AWTransform() : Position(0.0f), Rotation(0.0f), Scale(1.0f) {}
	// Assignment constructor
	AWTransform(Vector2 Position, float Rotation, Vector2 Scale) :
		Position(Position), Rotation(Rotation), Scale(Scale) {}
	// Transform constructor
	AWTransform(const AWTransform& Other) :
		Position(Other.Position), Rotation(Other.Rotation), Scale(Other.Scale) {}

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
};

class GameObject {
public:
	GameObject() : m_ShouldDestroy(false), m_IsOverlapping(false) {}
	virtual ~GameObject() = default;

	// Runs when this object spawns into the game
	void Start();
	// Listen for input events
	void ProcessInput(Input* GameInput);
	// Run every frame
	void Update(float DeltaTime);
	// Runs every frame after the update
	void PostUpdate(float DeltaTime);
	// Destroy the game object
	void DestroyObject();
	// Is the object pending destroy at the end of the loop
	bool IsPendingDestroy() const { return m_ShouldDestroy; }
	// Remove any memory references
	virtual void Cleanup();
	// Get the transform of the object
	// Position, Rotation, Scale
	AWTransform GetTransform() const { return m_Transform; }
	// Set the transform of the object
	virtual void SetTransform(AWTransform Transform);
	// Set the position of the object
	void SetPosition(Vector2 Position);
	// Set the rotation angle of the object
	void SetRotation(float Rotation);
	// Set the scale of the object
	void SetScale(Vector2 Scale);

	// Test which bounds event needs to run
	void TestOverLapEvent(Bounds* OtherBounds);
	// Return all bounds on the object
	TArray<Bounds*> GetAllBounds() const { return m_BoundsStack; }

protected:
	// Run when the game object has been marked for destroy
	virtual void OnDestroy();
	// Runs when the game object spawns into the game
	virtual void OnStart() {}
	// Run on the game objects process input (before update each frame)
	virtual void OnProcessInput(Input* GameInput) {}
	// Run on the game objects update (each frame)
	virtual void OnUpdate(float DeltaTime) {}
	// Run on the game objects post update (each frame after the update)
	virtual void OnPostUpdate(float DeltaTime) {}

	// This will run when a bounds enters another bounds
	// @param 1 - other bounds that overlapped
	// @param 2 - the game objects bounds that overlapped
	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) {};
	
	// This will run when a bounds exits another bounds
	// @param 1 - other bounds that were overlapped
	// @param 2 - the game objects bounds that were overlapped
	virtual void OnOverlapExit(Bounds* OverlapBounds, Bounds* HitBounds) {};

	// Add a bounds to the object
	Bounds* AddBounds(Vector2 Center = 0.0f, Vector2 Extent = 1.0f);

protected:
	// If the object is overlapping
	bool m_IsOverlapping;

private:
	// Set all bounds to match the object position
	void BoundsMatchObjectPosition();

private:
	// Determine if the object should be destroyed at the end of the loop
	bool m_ShouldDestroy;

	// Store the transform location for the object
	AWTransform m_Transform;
	
	// Store all of the bounds on the object
	TArray<Bounds*> m_BoundsStack;
};