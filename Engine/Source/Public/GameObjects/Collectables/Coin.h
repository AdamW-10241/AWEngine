#pragma once
#include "GameObjects/Collectables/Collectable.h"
#include "GameObjects/VFX/VFX_CollectCoin.h"

class Coin : public Collectable {
public: 
	Coin();

protected:
	virtual void PlayFX() override;
};