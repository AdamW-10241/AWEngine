#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Player : public DirectionalCharacter {
public:
	Player();

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;
};