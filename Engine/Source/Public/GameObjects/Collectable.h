#pragma once
#include "GameObjects/Character.h"

class Collectable : public Character {
public:
	Collectable();

protected:
	virtual void OnStart() override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

protected:
	float m_ScoreValue;
};