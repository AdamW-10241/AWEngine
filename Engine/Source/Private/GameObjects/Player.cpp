#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/PlayerProjectile.h"
#include "Game.h"

#include "Debug.h"

#define Super Character

#define ENGINE_IDLE 0
#define ENGINE_POWERED 1

#define WEAPON_LASER 0
#define WEAPON_ROCKET 1

Player::Player()
{
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;

	m_Scale = 3.0f;
	m_Size = 48.0f - 16.0f;

	m_InstantFireToggle = false;
	m_TripleShotToggle = false;
	m_AltProjectileSprite = false;
	m_InvincibleToggle = false;
	m_ReversedControlsToggle = false;

	m_BaseRateOfFire = 0.25f;
	m_RateOfFire = m_BaseRateOfFire;
	m_FireTimer = 0.0f;

	m_MaxLives = 3;
	m_Lives = m_MaxLives;

	// Add engine sprite
	AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engines/PNGs/Main Ship - Engines - Supercharged Engine.png"
	);

	// Add ship base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png"
	);

	AnimationParams AnimParamsEngine;
	AnimParamsEngine.fps = 24;
	AnimParamsEngine.FrameHeight = 48;
	AnimParamsEngine.FrameWidth = 48;
	AnimParamsEngine.EndFrame = 3;
	AnimParamsEngine.MaxFrames = 4;

	// Add the idle engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParamsEngine
	));

	// Add the powered engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParamsEngine
	));

	AnimationParams AnimParamsWeaponLaser;
	AnimParamsWeaponLaser.fps = 48;
	AnimParamsWeaponLaser.FrameHeight = 48;
	AnimParamsWeaponLaser.FrameWidth = 48;
	AnimParamsWeaponLaser.EndFrame = 11;
	AnimParamsWeaponLaser.MaxFrames = 12;

	// Add the laser weapon
	m_Weapons.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Weapons/PNGs/Main Ship - Weapons - Big Space Gun.png",
		&AnimParamsWeaponLaser
	));

	AnimationParams AnimParamsWeaponRocket;
	AnimParamsWeaponRocket.fps = 24;
	AnimParamsWeaponRocket.FrameHeight = 48;
	AnimParamsWeaponRocket.FrameWidth = 48;
	AnimParamsWeaponRocket.EndFrame = 16;
	AnimParamsWeaponRocket.MaxFrames = 17;

	// Add the laser weapon
	m_Weapons.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Weapons/PNGs/Main Ship - Weapons - Rockets.png",
		&AnimParamsWeaponRocket
	));

	SetPoweredEngine(false);
	SetWeapon(WEAPON_LASER, false);
	
	SetScale(m_Scale);

	Bounds* PlayerBounds = AddBounds(0.0f, ScaledSize());
	PlayerBounds->m_OriginOffset = -ScaledHalfSize();
	PlayerBounds->m_Debug = false;
}

void Player::OnProcessInput(Input* GameInput)
{
	if (m_Lives <= 0) {
		return;
	}
	
	Super::OnProcessInput(GameInput);

	int ReversedControlFactor = m_ReversedControlsToggle ? -1 : 1;
	
	if (GameInput->IsKeyDown(AW_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f * ReversedControlFactor));
	}
	if (GameInput->IsKeyDown(AW_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f * ReversedControlFactor));
	}
	if (GameInput->IsKeyDown(AW_KEY_A)) {
		AddMovementInput(Vector2(-1.0f * ReversedControlFactor, 0.0f));
	}
	if (GameInput->IsKeyDown(AW_KEY_D)) {
		AddMovementInput(Vector2(1.0f * ReversedControlFactor, 0.0f));
	}

	if (m_FireTimer <= 0.0f) {
		if (GameInput->IsKeyDown(AW_KEY_SPACE)) {
			// Check triple shot
			if (m_TripleShotToggle) {
				SpawnTripleShot();
			}
			else {
				SpawnProjectile();
			}

			m_FireTimer = m_RateOfFire;
		}
	}
}

void Player::OnUpdate(float DeltaTime)
{
	if (m_Lives <= 0) {
		return;
	}
	
	Super::OnUpdate(DeltaTime);

	if (m_FireTimer > 0.0f) {
		m_FireTimer -= DeltaTime;
	}

	SetPoweredEngine(m_MoveDirection.Length() > 0.0f);
	SetWeapon(!m_AltProjectileSprite, m_FireTimer > 0.0f);
}

void Player::SetPoweredEngine(bool Powered)
{
	if (m_EngineEffects.size() > 1) {
		if (m_EngineEffects[ENGINE_IDLE] != nullptr && m_EngineEffects[ENGINE_POWERED] != nullptr) {
			m_EngineEffects[ENGINE_IDLE]->SetActive(!Powered);
			m_EngineEffects[ENGINE_POWERED]->SetActive(Powered);
		}
	}
}

void Player::SetWeapon(bool Weapon, bool Firing)
{
	if (m_Weapons.size() > 1) {
		if (m_Weapons[WEAPON_LASER] != nullptr && m_Weapons[WEAPON_ROCKET] != nullptr) {
			m_Weapons[WEAPON_LASER]->SetActive(Weapon);
			m_Weapons[WEAPON_ROCKET]->SetActive(!Weapon);

			if (!Firing) {
				m_Weapons[WEAPON_LASER]->m_Sprite->SetFirstFrame();
				m_Weapons[WEAPON_ROCKET]->m_Sprite->SetFirstFrame();
			}
		}
	}
}

void Player::SpawnProjectile(Vector2 MoveDir, bool AltProjectileSprite)
{
	// Spawning the game object / projectile
	PlayerProjectile* Proj = Game::GetGame()->AddGameObject<PlayerProjectile>();

	if (m_AltProjectileSprite) {
		Proj->SetAltSprite();
	}

	if (m_TripleShotToggle) {
		Proj->SetRotation((float)atan2(MoveDir.y, MoveDir.x) * 180 / (float)M_PI + 90);
	}

	// Reposition the projectile
	Vector2 SpawnPos = GetTransform().Position;
	SpawnPos.y -= ScaledHalfSize();

	Proj->SetPosition(SpawnPos);

	// Firing the projectile
	Proj->FireProjectile(this, MoveDir);
}

void Player::SpawnTripleShot()
{
	SpawnProjectile({ -1.0f, -1.0f });
	SpawnProjectile({ 0.0f, -1.0f });
	SpawnProjectile({ 1.0f, -1.0f });
}

void Player::OnDeath(GameObject* DeathCauser)
{
	for (auto Item : GetAllSprites()) {
		Item->SetActive(false);
	}

	for (auto Item : GetAllBounds()) {
		Item->DestroyBounds();
	}
}
