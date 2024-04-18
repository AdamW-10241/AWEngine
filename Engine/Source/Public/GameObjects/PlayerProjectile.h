#pragma once
#include "GameObjects/Projectile.h"

class PlayerProjectile : public Projectile {
public:
	PlayerProjectile();

	void SetAltSprite() { m_AltSprite = true; }

protected:
	virtual void OnStart();

protected:
	bool m_AltSprite;
};