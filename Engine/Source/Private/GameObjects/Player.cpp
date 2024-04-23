#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/PlayerProjectile.h"
#include "Game.h"
#include "SDL2/SDL_mixer.h"

#include "Debug.h"

#define Super DirectionalCharacter

#define PI 3.1415926f

Player::Player()
{
	// Set variables
	m_BaseRateOfFire = 0.2f;
	m_RateOfFire = m_BaseRateOfFire;
	m_FireTimer = 0.0f;
	m_MaxLives = 3;
	m_Lives = m_MaxLives;

	m_Scale = 3.0f;
	m_Size = 48.0f - 16.0f;

	m_InstantFireToggle = false;
	m_TripleShotToggle = false;

	// Default values
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
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
	PlayerBounds->m_Debug = false;
	
	// Set the scale
	SetScale(m_Scale);

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
				SpawnTripleShot(GameInput->GetMousePos());
			}
			else {
				SpawnProjectile(GameInput->GetMousePos());
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

	// Screen border
	ScreenBorder(ScaledHalfSize());
}

void Player::SpawnProjectile(Vector2 MoveDir, Vector2 MousePosition)
{
	// Spawning the game object / projectile
	PlayerProjectile* Proj = Game::GetGame()->AddGameObject<PlayerProjectile>();

	// Reposition the projectile
	Vector2 PlayerPosition = GetTransform().Position;
	PlayerPosition.y -= ScaledHalfSize();

	Proj->SetPosition(PlayerPosition);

	// Rotate projectile based on angle between mouse and player
	Proj->SetRotation(
		atan2((MousePosition.y - PlayerPosition.y), (MousePosition.x - PlayerPosition.x)) * 180 / PI
	);

	// Firing the projectile
	Proj->FireProjectile(this, MoveDir);

	int SoundIndex = 0; // rand() % 3;

	if (m_ShootSFX[SoundIndex] != nullptr) {
		Mix_PlayChannel(-1, m_ShootSFX[SoundIndex], 0);
	}
}

void Player::SpawnTripleShot(Vector2 MousePosition)
{
	SpawnProjectile({ -1.0f, -1.0f }, MousePosition);
	SpawnProjectile({ 0.0f, -1.0f }, MousePosition);
	SpawnProjectile({ 1.0f, -1.0f }, MousePosition);
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
