#include "GameObjects/Enemy.h"
#include "GameObjects/Player.h"
#include "GameObjects/Collectable.h"
#include "GameObjects/VFX/VFX_EnemyExplosion.h"
#include "Game.h"

#include "Debug.h"

#define Super DirectionalCharacter

Enemy::Enemy()
{
	// Set variables
	m_MaxLives = 1;
	m_Lives = m_MaxLives;

	m_Scale = 3.5f;
	m_Size = 16.0f;

	m_TimeUntilNextMovementChoice = 0.0f;
	m_ScoreValue = 100.0f;
	m_PlayerRef = nullptr;

	// Default values
	m_MaxSpeed = 200.0f;
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

	// Add bounds
	Bounds* EnemyBounds = AddBounds(0.0f, ScaledSize());
	EnemyBounds->m_OriginOffset = -ScaledHalfSize();
	EnemyBounds->m_Tag = "ENEMY";
	EnemyBounds->m_TargetTag = "PLAYER";
	EnemyBounds->m_Debug = false;

	// Set the scale
	SetScale(m_Scale);

	// Pick random spawn spot
	SetPosition({ 1255.0f ,
		Game::GetGame()->GetRandomFloatRange(
			0.0f,
			Game::GetGame()->WindowHeightF())
	});
}

void Enemy::OnUpdate(float DeltaTime)
{
	// Randomly choose movement
	if (m_TimeUntilNextMovementChoice - DeltaTime <= 0.0f) {
		// Check player is valid
		if (m_PlayerRef == nullptr) {
			return;
		}

		// Randomly determine movement direction
		float const RangeConst = 2.0f;
		Vector2 RandomOffset = { Game::GetGame()->GetRandomFloatRange(-RangeConst, RangeConst),
			Game::GetGame()->GetRandomFloatRange(-RangeConst, RangeConst) };

		if (rand() % 3 <= 1) {
			// Toward player with random offset
			// 2/3 to follow
			m_MovementChoice = m_PlayerRef->GetTransform().Position - GetTransform().Position + (RandomOffset * 50.0f);
		}
		else {
			// Random direction
			// 1/3 to move randomly
			m_MovementChoice = RandomOffset;
		}

		// Randomly get time until next choice
		m_TimeUntilNextMovementChoice = rand() % 8;
	}

	// Reduce time until choice
	m_TimeUntilNextMovementChoice -= DeltaTime;

	// Add movement
	AddMovementInput(m_MovementChoice);

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

	// Randomly spawn a coin collectable
	if (rand() % 3 == 0) {
		auto SpawnedCollectable = Game::GetGame()->Game::AddGameObject<Collectable>();
		SpawnedCollectable->SetPosition(GetTransform().Position);
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
