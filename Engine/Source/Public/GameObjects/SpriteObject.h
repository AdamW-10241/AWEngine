#pragma once
#include "GameObjects/GameObject.h"
#include "Graphics/Animation.h"

class Sprite {
public:
	// Default construtor
	Sprite() : m_Sprite(nullptr), m_IsActive(true) {
		m_Offset.Scale = 0.0f;
	}

	// Sprite assign constructor
	Sprite(Animation* Anim) : m_Sprite(Anim), m_IsActive(true) {
		m_Offset.Scale = 0.0f;
	}

	~Sprite() {
		delete m_Sprite;
		m_Sprite = nullptr;
	}

	void SetActive(bool IsActive) {
		m_IsActive = IsActive;
		m_Sprite->SetVisible(IsActive);
	}

public:
	Animation* m_Sprite;
	AWTransform m_Offset;

private:
	bool m_IsActive;
};

class SpriteObject : public GameObject {
public:
	SpriteObject() = default;

	virtual void Cleanup() override;

protected:
	// Add an animation / sprite to the sprite stack
	Sprite* AddSprite(const char* PathToFile, AnimationParams* Params = nullptr);

	virtual void OnPostUpdate(float DeltaTime) override;

	// Get all the sprites attached to the object
	TArray<Sprite*> GetAllSprites() const { return m_SpriteStack; }

private:
	void SpriteFollowObject(Sprite* SpriteToFollow);

private:
	// Store all sprites related to this object
	TArray<Sprite*> m_SpriteStack;
};