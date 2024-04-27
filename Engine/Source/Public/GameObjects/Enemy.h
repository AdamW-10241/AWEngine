#pragma once
#include "GameObjects/DirectionalCharacter.h"

class Player;

class Enemy : public DirectionalCharacter {
public:
	Enemy(float DifficultyScale, float Scale);

	void SetPlayerRef(Player* PlayerRef) { m_PlayerRef = PlayerRef; }

	void ToggleFastMode();

protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser) override;

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

	void Move(float DeltaTime);

protected:
	// Time until the next movemnt choice is made
	float m_TimeUntilNextMovementChoice;

	// Movement made by the enemy until the next movement choice
	Vector2 m_MovementChoice;

	// Enemy score value
	float m_ScoreValue;

	// Player reference
	Player* m_PlayerRef;

	// Toggles
	float m_BaseMaxSpeed;

	bool m_FastMode;
};