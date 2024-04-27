#pragma once
#include "GameObjects/Character.h"

class DirectionalCharacter;
class Bounds;

struct Mix_Chunk;

enum W_SFX {
	W_SFX_MISS = 0,
	W_SFX_HIT,

	// Not a sound effect, just the number of SFX
	W_SFX_NUM
};

class Weapon : public Character {
public:
	Weapon(float DifficultyScale = 1.0f);

	void SetOwner(DirectionalCharacter* Owner);

	DirectionalCharacter* GetOwner() const { return m_Owner; }

	void SetTargetPosition(Vector2 TargetPosition) { m_TargetPosition = TargetPosition; }

	void SetActive(bool State);
	
	void Attack();

	virtual void AttackHit(Character* Char, bool DoDamage) {};

	bool IsAttacking() const { return m_AttackTimer > 0.0f; }

	void Cooldown() { m_CooldownTimer = m_CooldownDuration; }
	
	bool IsCooldown() const { return m_CooldownTimer > 0.0; }

	Mix_Chunk* GetSFX(W_SFX Index) const { return m_W_SFX[Index]; }

	virtual void Cleanup();

	// Toggles
	void ToggleProjectileSprites();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnPostUpdate(float DeltaTime) override;

	virtual void OnAttack() {}

	virtual void SetIdlePosition(float RadiusMultiplier = 1.0f);

	virtual void SetAimPosition(float RadiusMultiplier = 1.0f);

	virtual void SetAttackPosition(float RadiusMultiplier = 1.0f) { SetAimPosition(m_RadiusMultiplier); }

	virtual void CreateHitVFX(Vector2 Position) {}

	virtual void CreateMissVFX(Vector2 Position) {}

	virtual void AddWeaponBounds() {};

protected:
	// Store the owner reference
	DirectionalCharacter* m_Owner;

	// Store the weapon animations
	TArray<Sprite*> m_Animations;

	// Store sound effects
	Mix_Chunk* m_W_SFX[W_SFX_NUM] = { nullptr };

	// Positional values
	Vector2 m_TargetPosition;

	float m_RotationOffset;

	float m_RadiusMultiplier;

	// Weapon state
	bool m_Active;

	// Weapon stats
	float m_Damage;

	float m_CooldownDuration;

	float m_CooldownTimer;

	float m_AttackDuration;

	float m_AttackTimer;

	// Toggles
	bool m_ToggleProjectileSprites;
};