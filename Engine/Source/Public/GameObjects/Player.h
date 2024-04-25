#pragma once
#include "GameObjects/DirectionalCharacter.h"

struct Mix_Chunk;

class Player : public DirectionalCharacter {
public:
	Player();

	// Set instant fire
	void SetInstantFire() {
		m_InstantFireToggle = !m_InstantFireToggle;
	}

	// Set triple shot
	void SetTripleShot() {
		m_TripleShotToggle = !m_TripleShotToggle;
	}

	virtual void Cleanup() override;

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

	void SpawnProjectile(Vector2 MousePosition = { 0.0f });

	void SpawnTripleShot(Vector2 MousePosition = { 0.0f });

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Store sound effects
	Mix_Chunk* m_ShootSFX[1] = { nullptr };

	// Toggles for firing projectiles
	bool m_InstantFireToggle, m_TripleShotToggle;
};