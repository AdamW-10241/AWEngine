#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Enemy : public DirectionalCharacter {
public:
	Enemy();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;
};