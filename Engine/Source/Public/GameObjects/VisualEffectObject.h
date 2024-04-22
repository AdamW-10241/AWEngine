#pragma once
#include "GameObjects/SpriteObject.h"

class VisualEffectObject : public SpriteObject {
public:
	VisualEffectObject();
	~VisualEffectObject() = default;
	
	int m_Loops;

protected:
	virtual void OnStart();

	virtual void OnUpdate(float DeltaTime);

	void LifeTimer(float DeltaTime);

protected:
	// Play length of the effect
	float m_Length;

	// Timer to destroy the effect
	float m_LifeTimer;
};