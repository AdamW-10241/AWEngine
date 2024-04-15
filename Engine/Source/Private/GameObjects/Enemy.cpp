#include "GameObjects/Enemy.h"
#include "GameObjects/Player.h"
#include "Game.h"

#include "Debug.h"

#define Super Character

Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;

	m_Scale = 3.0f;
	m_Size = 48.0f - 16.0f;

	m_Lives = 3;

	m_ScoreValue = 100.0f;
	
	// Add enemy base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Very damaged.png"
	);

	// Set the scale
	SetScale(m_Scale);

	// Flip the enemy to look downward
	SetRotation(180.0f);

	Bounds* EnemyBounds = AddBounds(0.0f, ScaledSize());
	EnemyBounds->m_OriginOffset = -ScaledHalfSize();
	EnemyBounds->m_Tag = "ENEMY";
	EnemyBounds->m_Debug = false;
}

void Enemy::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().Position.y - ScaledHalfSize() > 720.0f) {
		DestroyObject();
	}
}

void Enemy::OnDeath(GameObject* DeathCauser)
{
	if (auto PlayerTest = dynamic_cast<Player*>(DeathCauser)) {
		Game::GetGame()->m_Score += m_ScoreValue;
	}
	
	Super::OnDeath(DeathCauser);
}

void Enemy::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Is the owner of the bounds we overlapped with a player
	if (auto PlayerRef = dynamic_cast<Player*>(OverlapBounds->GetOwner())) {
		PlayerRef->ApplyDamage(this, 1);
		DestroyObject();
	}
}
