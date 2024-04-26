#pragma once
#include "GameObjects/Collectables/Collectable.h"
#include "GameObjects/VFX/VFX_CollectKey.h"

class Key : public Collectable {
public:
	Key();

protected:
	virtual void PlayFX() override { OnPlayFX<VFX_CollectKey>(); }
};