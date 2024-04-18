#pragma once
#include "GameObjects/Character.h"

class Enemy : public Character {
public:
	Enemy();

	// Toggles
	void SetAltSprite() { m_AltSprite = true; }
	void SetFastMode() { m_MaxSpeed *= 2.5f; }

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

protected:
	float m_ScoreValue;

	bool m_AltSprite;

private:
	Vector2 m_MoveDir;
	float m_RotationAmount;
};