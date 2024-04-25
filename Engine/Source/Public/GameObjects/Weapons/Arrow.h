#pragma once
#include "GameObjects/Weapons/Projectile.h"

class Arrow : public Projectile {
public:
	Arrow();

	virtual void FireProjectile() override;

protected:
	virtual void CreateVFX(DirectionalCharacter* Char) override;
};