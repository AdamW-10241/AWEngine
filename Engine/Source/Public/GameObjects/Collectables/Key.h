#pragma once
#include "GameObjects/Collectables/Collectable.h"
#include "GameObjects/VFX/VFX_CollectKey.h"

class Key : public Collectable {
public:
	Key();

protected:
	virtual void CollectCollectable() override;

	virtual void PlayFX() override;
};