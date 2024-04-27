#pragma once
#include "GameStates/Levels/PlayState.h"

class LevelStateThird : public PlayState {
public:
	LevelStateThird(float DifficultyScale) { m_DifficultyScale = DifficultyScale; }

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;
};