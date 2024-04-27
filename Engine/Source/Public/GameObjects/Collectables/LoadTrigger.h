#pragma once
#include "GameObjects/Collectables/Collectable.h"

class PlayState;

class LoadTrigger : public Collectable {
public:
	LoadTrigger();

protected:
	virtual void CollectCollectable();

protected:
	// Store pointer to next level
	///PlayState* m_NextLevel;
};