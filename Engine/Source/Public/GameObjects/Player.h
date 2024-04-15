#pragma once
#include "GameObjects/Character.h"

class Player : public Character {
public:
	Player();

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	// Change the engine effects animations
	void SetPoweredEngine(bool Powered);

	void SpawnProjectile();

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Timer values for firing projectiles
	float m_RateOfFire, m_FireTimer;
};