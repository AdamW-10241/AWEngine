#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"
#include "GameStates/GameStateMachine.h"
#include "Game.h"
#include "GameObjects/Projectile.h"

#include "Debug.h"

#define Super DirectionalCharacter

#define SCALE 4.0f
#define SIZE (16.0f) * SCALE
#define HALF_SIZE (SIZE / 2.0f)

#define PI 3.1415926f

Player::Player()
{
	// Set variables
	m_FireDelay = 0.0f;
	m_Dead = false;
	
	// Default values
	m_MaxSpeed = 400.0f;
	m_Deceleration = 7.0f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams AnimParams;
	AnimParams.fps = 12;
	AnimParams.FrameHeight = 16;
	AnimParams.FrameWidth = 16;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add player sprite: idle, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Right.png"
	));

	// Add player sprite: idle, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Left.png"
	));

	// Add player sprite: idle, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Up.png"
	));

	// Add player sprite: idle, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Idle-Down.png"
	));

	// Add player sprite: moving, right
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Right.png",
		&AnimParams
	));

	// Add player sprite: moving, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Left.png",
		&AnimParams
	));

	// Add player sprite: moving, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Up.png",
		&AnimParams
	));

	// Add player sprite: moving, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Down.png",
		&AnimParams
	));

	// Set base animation state
	m_LastMovementDirection = DIRECTION_DOWN;
	SetAnimation(m_LastMovementDirection, true);

	// Add bounds
	Bounds* PlayerBounds = AddBounds({ 640.0f, 360.0f }, SIZE);
	PlayerBounds->m_OriginOffset = -HALF_SIZE;
	PlayerBounds->m_Tag = "PLAYER";
	PlayerBounds->m_Debug = false;
}

void Player::OnStart()
{
	Super::OnStart();
	
	SetPosition({ 640.0f, 360.0f });
	SetScale(SCALE);
}

void Player::OnProcessInput(Input* GameInput)
{
	Super::OnProcessInput(GameInput);
	
	if (GameInput->IsKeyDown(AW_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_A)) {
		AddMovementInput(Vector2(-1.0f, 0.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_D)) {
		AddMovementInput(Vector2(1.0f, 0.0f));
	}

	if (GameInput->IsMouseButtonDown(AW_MOUSE_LEFT)) {
		FireProjectile(GameInput->GetMousePos());
	}
}

void Player::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Reduce fire delay
	m_FireDelay -= DeltaTime;

	// Screen border
	ScreenBorder(HALF_SIZE);
}

void Player::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	// Stop overlap code if dead
	if (m_Dead) {
		return;
	}
	
	if (OverlapBounds->m_Tag == "ENEMY") {
		// Change to game over state
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(new GameOverState());
		AW_LOG("Player", "GameState changed to the GameOverState");

		// Set dead flag
		m_Dead = true;
	}
}

void Player::Cleanup()
{
	// Destroy projectiles
	for (const auto Item : m_Projectiles) {
		if (Item != nullptr) {
			Item->DestroyObject();
			AW_LOG("Player", "Cleaned up projectile.");
		}
	}

	Super::Cleanup();
}

void Player::CollectGarbage()
{
	// Delete marked projectiles
	std::erase_if(m_Projectiles,
		[](Projectile* Item) {
			if (!Item->IsPendingDestroy()) {
				return false;
			}

			AW_LOG("Player", "Removed destroy-marked projectile from stack.");
			return true; }
	);

	Super::CollectGarbage();
}

void Player::FireProjectile(Vector2 AimPosition)
{
	if (m_Projectiles.size() >= 2 || m_FireDelay > 0.0f) {
		return;
	}

	// Add new projectile
	m_Projectiles.push_back(
		Game::GetGame()->GetGameStateMachine()->GetActiveGameState()->AddGameObject<Projectile>()
	);

	// Set the projectiles position to match the player
	m_Projectiles.back()->SetPosition(GetTransform().Position);

	// Angle projectile toward cursor
	Vector2 PlayerPosition = GetTransform().Position;

	m_Projectiles.back()->SetRotation(
		// Calculate angle from aim position and player position
		atan2((AimPosition.y - PlayerPosition.y), (AimPosition.x - PlayerPosition.x)) * 180 / PI
	);

	// Move projectile toward cursor
	m_Projectiles.back()->AddForce(AimPosition - PlayerPosition, 1000.0f);

	// Set fire delay
	m_FireDelay = 0.2f;
}