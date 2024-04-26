#pragma once
#include "GameObjects/Character.h"\

struct Mix_Chunk;

class Collectable : public Character {
public:
	Collectable();

	virtual void Cleanup();

protected:
	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
	
	virtual void CollectCollectable() {};

	virtual void PlayFX();

protected:
	// Collectable score value
	float m_ScoreValue;

	// Collect sound
	Mix_Chunk* m_C_SFX;
};