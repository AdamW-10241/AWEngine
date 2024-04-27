#include "GameObjects/Enemy.h"
#include "GameObjects/Player.h"
#include "GameObjects/Collectables/Coin.h"
#include "GameObjects/VFX/VFX_EnemyExplosion.h"
#include "GameObjects/Weapons/Sword.h"
#include "GameObjects/Weapons/Bow.h"

#include "Game.h"

#include "Debug.h"

#define Super DirectionalCharacter

Enemy::Enemy(float DifficultyScale, float Scale)
{
	// Set variables
	m_DifficultyScale = DifficultyScale;

	m_MaxHealth = m_DifficultyScale;
	m_Health = m_MaxHealth;

	m_Scale = Scale; // 3.5f
	m_Size = 16.0f;

	m_TimeUntilNextMovementChoice = 0.0f;
	m_ScoreValue = 100.0f;

	m_PlayerRef = nullptr;
	m_Tag = "ENEMY";
	m_TargetTag = "PLAYER";

	// Default values
	m_MaxSpeed = 125.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 1000.0f;

	AnimationParams AnimParams;
	AnimParams.fps = 12;
	AnimParams.FrameHeight = 16;
	AnimParams.FrameWidth = 16;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add enemy sprite: idle, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Right.png"
	));

	// Add enemy sprite: idle, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Left.png"
	));

	// Add enemy sprite: idle, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Up.png"
	));

	// Add enemy sprite: idle, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Idle-Down.png"
	));

	// Add enemy sprite: moving, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Right.png",
		&AnimParams
	));

	// Add enemy sprite: moving, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Left.png",
		&AnimParams
	));

	// Add enemy sprite: moving, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Up.png",
		&AnimParams
	));

	// Add enemy sprite: moving, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/Skeleton/SeparateAnim/Adjusted Animations/Moving-Down.png",
		&AnimParams
	));

	// Set base animation state
	m_LastMovementDirection = DIRECTION_DOWN;
	SetAnimation(m_LastMovementDirection, true);

	// Add weapons
	if (rand() % 3 == 0) {
		AddWeapon(Game::GetGame()->AddGameObject<Bow>(m_DifficultyScale));
	}
	else {
		AddWeapon(Game::GetGame()->AddGameObject<Sword>(m_DifficultyScale));
	}

	UpdateWeaponStates();
}

void Enemy::OnUpdate(float DeltaTime)
{
	// Randomly choose movement
	Move(DeltaTime);

	// Reduce time until choice
	m_TimeUntilNextMovementChoice -= DeltaTime;

	// Add movement
	AddMovementInput(m_MovementChoice);

	// Attack if condition met
	Attack(m_PlayerRef->GetTransform().Position, rand() % 175 == 0);

	Super::OnUpdate(DeltaTime);

	// Screen border
	ScreenBorder(ScaledHalfSize());
}

void Enemy::OnDeath(GameObject* DeathCauser)
{
	if (auto PlayerTest = dynamic_cast<Player*>(DeathCauser)) {
		Game::GetGame()->m_Score += m_ScoreValue;
	}

	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_EnemyExplosion>();
	VFX->SetPosition(GetTransform().Position);
	VFX->SetScale(m_Scale);

	// Randomly spawn a coin
	if (rand() % 3 == 0) {
		const auto SpawnedCoin = Game::GetGame()->Game::AddGameObject<Coin>();
		SpawnedCoin->SetPosition(GetTransform().Position);
	}

	// Mark killed enemy
	((PlayState*)Game::GetGame()->GetGameStateMachine()->GetActiveGameState())->EnemyKilled();
	
	Super::OnDeath(DeathCauser);
}

void Enemy::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Is the owner of the bounds we overlapped with a player
	if (auto PlayerRef = dynamic_cast<Player*>(OverlapBounds->GetOwner())) {
		PlayerRef->ApplyDamage(this, 1);
		ApplyDamage(PlayerRef, 1);
	}
}

void Enemy::Move(float DeltaTime)
{
	// Handle movement
	if (m_TimeUntilNextMovementChoice <= 0.0f) {
		// Determine movement direction
		if (rand() % 10 == 0) {
			// Toward Screen Center
			m_MovementChoice = Game::GetGame()->GetScreenCenter() - GetTransform().Position;
		}
		else {
			// Toward player with random offset
			m_MovementChoice = m_PlayerRef->GetTransform().Position - GetTransform().Position;
		}

		// Get time until next choice
		m_TimeUntilNextMovementChoice = rand() % 5;
	}
}
