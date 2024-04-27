#pragma once
#include "GameObjects/Collectables/Collectable.h"

class PlayState;

class LoadTrigger : public Collectable {
public:
	LoadTrigger(uint32_t NextLevel, float DifficultyScale, float Scale);

	void SetActive();

protected:
	virtual void OnStart();
	
	virtual void CollectCollectable() override;

protected:
	// Store pointer to next level
	uint32_t m_NextLevel;

	// Store difficulty scale for next level
	float m_DifficultyScale;

	// Active state
	bool m_Active;
};