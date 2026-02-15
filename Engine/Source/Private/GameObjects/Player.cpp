#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/Weapons/Sword.h"
#include "GameObjects/Weapons/Bow.h"

#include "Input.h"
#include "Game.h"
#include "SDL2/SDL_mixer.h"
#include <cmath>

#include "Debug.h"

#define Super DirectionalCharacter

Player::Player(float Scale)
{
	// Set variables
	m_MaxHealth = 10;
	m_Health = m_MaxHealth;

	m_Scale = Scale; // 3.5f
	m_Size = 16.0f;

	m_Tag = "PLAYER";
	m_TargetTag = "ENEMY";

	m_BaseDashTimer = 2.0f;
	m_DashTimer = 0.0f;

	m_DashMultiplier = 3.0f;
	
	m_ToggleInvincible = false;
	m_ToggleReversedControls = false;

	// Default values
	m_BaseMaxSpeed = 300.0f;
	m_MaxSpeed = m_BaseMaxSpeed;

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
		false,
		&AnimParams
	));

	// Add player sprite: moving, left
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Left.png",
		false,
		&AnimParams
	));

	// Add player sprite: moving, up
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Up.png",
		false,
		&AnimParams
	));

	// Add player sprite: moving, down
	m_DirectionSprites.push_back(AddSprite(
		"Content/NinjaAdventure/Actor/Characters/MaskFrog/SeparateAnim/Adjusted Animations/Moving-Down.png",
		false,
		&AnimParams
	));

	// Set base animation state
	m_LastMovementDirection = DIRECTION_DOWN;
	SetAnimation(m_LastMovementDirection, true);

	// Add weapons
	AddWeapon(Game::GetGame()->AddGameObject<Sword>());
	AddWeapon(Game::GetGame()->AddGameObject<Bow>());

	UpdateWeaponStates();

	// Load sound effects
	m_DC_SFX[DC_SFX_DEATH] = SoundManager::Get().LoadSound("Content/Audio/DEATH_SFX_PLAYER.wav");
	Mix_VolumeChunk(m_DC_SFX[DC_SFX_DEATH], 100);
}

void Player::OnProcessInput(Input* GameInput)
{
	if (m_Health <= 0) {
		return;
	}

	Super::OnProcessInput(GameInput);

	// Reverse controls if set
	int ReverseFactor = m_ToggleReversedControls ? -1 : 1;

	if (GameInput->IsKeyDown(AW_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f * ReverseFactor));
	}
	if (GameInput->IsKeyDown(AW_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f * ReverseFactor));
	}
	if (GameInput->IsKeyDown(AW_KEY_A)) {
		AddMovementInput(Vector2(-1.0f * ReverseFactor, 0.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_D)) {
		AddMovementInput(Vector2(1.0f * ReverseFactor, 0.0f));
	}

	// Dash
	if (GameInput->IsKeyDown(AW_KEY_LSHIFT)) {
		if (m_DashTimer <= 0.0f) {
			m_MaxSpeed = m_BaseMaxSpeed * m_DashMultiplier;

			m_DashTimer = m_BaseDashTimer;
		}
	}

	// Scroll weapon if condition met
	if (int ScrollAmount = GameInput->GetMouseScroll(); ScrollAmount != 0) {
		// Check sign of scroll to determine forward or backward scrolling
		bool SwitchCondition = !std::signbit((float)ScrollAmount);
		SwitchWeapon(SwitchCondition);
	}

	// Attack if condition met
	Attack(GameInput->GetMousePos(), GameInput->IsMouseButtonDown(AW_MOUSE_LEFT));
}

void Player::OnUpdate(float DeltaTime)
{
	// Invincibility
	if (m_ToggleInvincible) {
		if (m_Health < m_MaxHealth) {
			m_Health = m_MaxHealth;
		}
	}

	// Skip if dead
	if (m_Health <= 0) return;

	// Decelerate after dash
	if (m_MaxSpeed > m_BaseMaxSpeed) {
		m_MaxSpeed -= DeltaTime * m_BaseMaxSpeed * 5.0f;
	}
	else {
		m_MaxSpeed = m_BaseMaxSpeed;
	}
	
	Super::OnUpdate(DeltaTime);

	// Decrease time until next dash
	if (m_DashTimer > 0.0f) {
		m_DashTimer -= DeltaTime;
	}

	// Screen border
	ScreenBorder(ScaledHalfSize());
}

void Player::OnDeath(GameObject* DeathCauser, bool doDestroy)
{
	for (auto Item : GetAllSprites()) {
		Item->SetActive(false);
	}

	for (auto Item : GetAllBounds()) {
		Item->DestroyBounds();
	}

	Super::OnDeath(DeathCauser, false);
}
