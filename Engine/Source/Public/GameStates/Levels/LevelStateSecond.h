#pragma once
#include "GameStates/Levels/PlayState.h"

class LevelStateSecond : public PlayState {
public:
	LevelStateSecond(float DifficultyScale) { m_DifficultyScale = DifficultyScale; }

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;
};