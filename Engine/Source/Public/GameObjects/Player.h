#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Player : public DirectionalCharacter {
public:
	Player(float Scale);

	// Get dash
	float GetBaseDash() const { return m_BaseDashTimer; }

	float GetCurrentDash() const { return m_DashTimer; }

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Timers
	float m_BaseDashTimer;

	float m_DashTimer;

	float m_DashMultiplier;

	float m_BaseMaxSpeed;
};