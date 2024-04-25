#pragma once
#include "GameObjects/Weapons/Projectile.h"

class Arrow : public Projectile {
public:
	Arrow();

	virtual void FireProjectile() override;

protected:
	virtual void CreateHitVFX(Vector2 Position) override;

	virtual void CreateMissVFX(Vector2 Position) override;
};