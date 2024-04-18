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

	m_MaxLives = 3;
	m_Lives = m_MaxLives;

	m_ScoreValue = 100.0f;
	
	m_AltSprite = false;

	m_MoveDir = { 0.0f, 1.0f };
	m_RotationAmount = 0.0f;

	// Set the scale
	SetScale(m_Scale);

	// Flip the enemy to look downward
	SetRotation(180.0f);

	Bounds* EnemyBounds = AddBounds(0.0f, ScaledSize());
	EnemyBounds->m_OriginOffset = -ScaledHalfSize();
	EnemyBounds->m_Tag = "ENEMY";
	EnemyBounds->m_Debug = false;
}

void Enemy::OnStart()
{
	// Add enemy base sprite
	const char* PathToFile = "Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Very damaged.png";

	if (m_AltSprite) {
		// Alt
		PathToFile = "Content/Space/Asteroids/PNGs/Asteroid 01 - Base.png";
		m_MoveDir = { Game::GetGame()->GetRandomFloatRange(-0.75f, 0.75f), 1.0f };
		m_RotationAmount = Game::GetGame()->GetRandomFloatRange(-100.0f, 100.0f);
	}

	m_MainSprite = AddSprite(PathToFile);
}

void Enemy::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	AddMovementInput(m_MoveDir);
	SetRotation(GetTransform().Rotation + m_RotationAmount * DeltaTime);

	if (GetTransform().Position.y - ScaledHalfSize() > 720.0f) {
		DestroyObject();
	}
}

void Enemy::OnDeath(GameObject* DeathCauser)
{
	if (auto PlayerTest = dynamic_cast<Player*>(DeathCauser)) {
		Game::GetGame()->m_Score += (int)m_ScoreValue;
	}
	
	Super::OnDeath(DeathCauser);
}

void Enemy::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Is the owner of the bounds we overlapped with a player
	if (auto PlayerRef = dynamic_cast<Player*>(OverlapBounds->GetOwner())) {
		// Deal damage if not invincible
		if (!PlayerRef->GetInvinciblityState()) {
			PlayerRef->ApplyDamage(this, 1);
		}
		// Destroy enemy regardless in state
		DestroyObject();
	}
}
