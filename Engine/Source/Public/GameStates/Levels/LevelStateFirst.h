#pragma once
#include "GameStates/Levels/PlayState.h"

class LevelStateFirst : public PlayState {
public:
	LevelStateFirst(float DifficultyScale) { m_DifficultyScale = DifficultyScale; }

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;
};