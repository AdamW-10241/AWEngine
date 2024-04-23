#pragma once
#include "GameObjects/DirectionalCharacter.h"

struct Mix_Chunk;

class Player : public DirectionalCharacter {
public:
	Player();

	// Set instant fire
	void SetInstantFire() {
		m_InstantFireToggle = !m_InstantFireToggle;
		m_RateOfFire = (m_InstantFireToggle == false) ? m_BaseRateOfFire : 0.05f;
	}

	// Set triple shot
	void SetTripleShot() {
		m_TripleShotToggle = !m_TripleShotToggle;
	}

	virtual void Cleanup() override;

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	void SpawnProjectile(Vector2 MousePosition = {0.0f});

	void SpawnTripleShot(Vector2 MousePosition = {0.0f});

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Store sound effects
	Mix_Chunk* m_ShootSFX[1] = { nullptr };

	// Toggles for firing projectiles
	bool m_InstantFireToggle, m_TripleShotToggle;

	// Timer values for firing projectiles
	float m_BaseRateOfFire;
	float m_RateOfFire;
	float m_FireTimer;
};