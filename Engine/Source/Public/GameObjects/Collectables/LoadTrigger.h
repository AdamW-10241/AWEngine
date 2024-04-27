#pragma once
#include "GameObjects/Collectables/Collectable.h"

class PlayState;

class LoadTrigger : public Collectable {
public:
	LoadTrigger(uint32_t NextLevel);

protected:
	virtual void CollectCollectable();

protected:
	// Store pointer to next level
	uint32_t m_NextLevel;
};