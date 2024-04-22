#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/PlayerProjectile.h"
#include "Game.h"
#include "SDL2/SDL_mixer.h"

#include "Debug.h"

#define Super Character

#define ENGINE_IDLE 0
#define ENGINE_POWERED 1

Player::Player()
{
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;

	m_Scale = 3.0f;
	m_Size = 48.0f - 16.0f;

	m_InstantFireToggle = false;
	m_TripleShotToggle = false;

	m_BaseRateOfFire = 0.2f;
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

	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 48;
	AnimParams.FrameWidth = 48;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add the idle engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParams
	));

	// Add the powered engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	SetPoweredEngine(false);
	
	SetScale(m_Scale);

	Bounds* PlayerBounds = AddBounds(0.0f, ScaledSize());
	PlayerBounds->m_OriginOffset = -ScaledHalfSize();
	PlayerBounds->m_Debug = false;

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

	if (m_MoveDirection.Length() > 0.0f) {
		SetPoweredEngine(true);
	}
	else {
		SetPoweredEngine(false);
	}
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

void Player::SpawnProjectile(Vector2 MoveDir)
{
	// Spawning the game object / projectile
	PlayerProjectile* Proj = Game::GetGame()->AddGameObject<PlayerProjectile>();

	// Reposition the projectile
	Vector2 SpawnPos = GetTransform().Position;
	SpawnPos.y -= ScaledHalfSize();

	Proj->SetPosition(SpawnPos);

	// Firing the projectile
	Proj->FireProjectile(this, MoveDir);

	int SoundIndex = 0; // rand() % 3;

	if (m_ShootSFX[SoundIndex] != nullptr) {
		Mix_PlayChannel(-1, m_ShootSFX[SoundIndex], 0);
	}
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
