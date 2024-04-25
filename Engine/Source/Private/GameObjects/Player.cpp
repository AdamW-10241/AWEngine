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

Player::Player()
{
	// Set variables
	m_MaxLives = 1;
	m_Lives = m_MaxLives;

	m_Scale = 3.5f;
	m_Size = 16.0f;

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
	Bounds* PlayerBounds = AddBounds(0.0f, ScaledSize());
	PlayerBounds->m_OriginOffset = -ScaledHalfSize();
	PlayerBounds->m_Tag = "PLAYER";
	PlayerBounds->m_TargetTag = "ENEMY";
	PlayerBounds->m_Debug = true;
	
	// Set the scale
	SetScale(m_Scale);

	// Add weapons
	Sword* PlayerSword = Game::GetGame()->AddGameObject<Sword>();
	AddWeapon(PlayerSword);

	Bow* PlayerBow = Game::GetGame()->AddGameObject<Bow>();
	AddWeapon(PlayerBow);

	UpdateWeaponStates();

	// Sound effects
	// https://freesound.org/people/SomeGuy22/sounds/519005/
	m_ShootSFX[0] = Mix_LoadWAV("Content/Audio/Laser1.wav");

	for (auto item : m_ShootSFX) {
		if (item != nullptr) {
			Mix_VolumeChunk(item, 15);
		}
	}
}

void Player::Cleanup()
{
	for (auto item : m_ShootSFX) {
		if (item != nullptr) {
			Mix_FreeChunk(item);
		}
	}
}

void Player::OnProcessInput(Input* GameInput)
{
	if (m_Lives <= 0) {
		return;
	}
	
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
	if (GameInput->IsKeyDown(AW_KEY_D)) {
		AddMovementInput(Vector2(1.0f, 0.0f));
	}

	// Scroll weapon if condition met
	ScrollSwitchWeapon(GameInput);

	// Attack if condition met
	Attack(GameInput->GetMousePos(), GameInput->IsMouseButtonDown(AW_MOUSE_LEFT));
}

void Player::OnUpdate(float DeltaTime)
{
	if (m_Lives <= 0) {
		return;
	}
	
	Super::OnUpdate(DeltaTime);

	// Screen border
	ScreenBorder(ScaledHalfSize());
}

void Player::OnDeath(GameObject* DeathCauser)
{
	for (auto Item : GetAllSprites()) {
		Item->SetActive(false);
	}

	for (auto Item : GetAllBounds()) {
		Item->DestroyBounds();
	}

	DestroyWeapons();
}

void Player::ScrollSwitchWeapon(Input* GameInput)
{
	// Check weapons array size
	if (m_OwnedWeapons.empty()) {
		return;
	}

	// Scroll switch weapon
	if (int ScrollAmount = GameInput->GetMouseScroll(); ScrollAmount != 0) {
		// Check scroll sign
		if (!std::signbit((float)ScrollAmount)) {
			// Scroll Up
			if (++m_UsedWeapon == m_OwnedWeapons.size()) { m_UsedWeapon = 0; }
		}
		else {
			// Scroll Down
			if (--m_UsedWeapon == uint32_t(-1)) { m_UsedWeapon = m_OwnedWeapons.size() - 1; }
		}

		// Update weapon states
		UpdateWeaponStates();
		
		AW_LOG("Player", "Scrolled weapon.");
	}
}
