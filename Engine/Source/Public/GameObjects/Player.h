#pragma once
#include "GameObjects/Character.h"

class Player : public Character {
public:
	Player();

	// Toggle instant fire
	void ToggleInstantFire() {
		m_InstantFireToggle = !m_InstantFireToggle;
		m_RateOfFire = (m_InstantFireToggle == false) ? m_BaseRateOfFire : 0.05f;
	}

	// Toggle triple shot
	void ToggleTripleShot() {
		m_TripleShotToggle = !m_TripleShotToggle;
	}

	// Toggle alt projectile sprite
	void ToggleAltProjectiles() { m_AltProjectileSprite = !m_AltProjectileSprite; }

	// Toggle invinciblity
	void ToggleInvincibility() { m_InvincibleToggle = !m_InvincibleToggle; }
	bool GetInvinciblityState() const { return m_InvincibleToggle; }

	// Toggle reversed controls
	void ToggleReversedControls() { m_ReversedControlsToggle = !m_ReversedControlsToggle; }

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	// Change the engine effects animations
	void SetPoweredEngine(bool Powered);

	// Change the engine effects animations
	void SetWeapon(bool Weapon, bool Firing);

	void SpawnProjectile(Vector2 MoveDir = {0.0f}, bool AltProjectileSprite = false);

	void SpawnTripleShot();

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Store the different weapons
	TArray<Sprite*> m_Weapons;

	// Toggles
	bool m_InstantFireToggle;
	bool m_TripleShotToggle;
	bool m_AltProjectileSprite;
	bool m_InvincibleToggle;
	bool m_ReversedControlsToggle;

	// Timer values for firing projectiles
	float m_BaseRateOfFire;
	float m_RateOfFire, m_FireTimer;
};