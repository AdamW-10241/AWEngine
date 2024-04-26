#pragma once
#include "GameStates/Levels/PlayState.h"

class LevelStateIntro : public PlayState {
public:
	LevelStateIntro() {}

protected:
	virtual void OnStart() override;
};