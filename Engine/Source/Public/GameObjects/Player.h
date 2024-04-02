#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Player : public DirectionalCharacter {
public:
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
};