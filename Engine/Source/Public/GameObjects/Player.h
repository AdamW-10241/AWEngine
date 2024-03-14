#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Player : public DirectionalCharacter{
public:
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;
};