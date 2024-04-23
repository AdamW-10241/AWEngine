#pragma once
#include "GameObjects/Character.h"

class Background : public Character {
public:
	Background() = default;

	void SetBackgroundSprite(const char* PathToFile);
};