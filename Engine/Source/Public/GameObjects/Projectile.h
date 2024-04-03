#pragma once
#include "GameObjects/Character.h"

class Projectile : public Character {
public:
	Projectile();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

private:
	void DestroyOffScreen(float HalfSpriteSize);
};