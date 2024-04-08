#pragma once
#include "GameObjects/Character.h"

class Enemy : public Character {
public:
	Enemy();

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser) override;

protected:
	float m_ScoreValue;
};