#pragma once
#include "GameObjects/Character.h"
#include "GameObjects/VFX/VisualEffectObject.h"

struct Mix_Chunk;

class Collectable : public Character {
public:
	Collectable();

protected:
	virtual void OnStart();

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
	
	virtual void CollectCollectable() {};

	virtual void PlayFX() {};

protected:
	// Collectable score value
	float m_ScoreValue;
};