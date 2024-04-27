#pragma once
#include "GameStates/Levels/PlayState.h"

class LevelStateFirst : public PlayState {
public:
	LevelStateFirst() {}

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;
};