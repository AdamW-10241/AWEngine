#include "GameObjects/DirectionalCharacter.h"

#include "Input.h"
#include "Game.h"
#include "GameObjects/VFX/VFX_Explosion.h"
#include "SDL2/SDL_mixer.h"

#include "Debug.h"

#define Super Character

DirectionalCharacter::DirectionalCharacter()
{
	// Set variables
	m_LastMovementDirection = 0;
	m_UsedWeapon = 0;
	m_DifficultyScale = 1.0f;
	m_Bounds = nullptr;

	m_Tag = "ALL";
	m_TargetTag = "ALL";
}

void DirectionalCharacter::ToggleProjectileSprites()
{
	// Toggle projectile
	for (Weapon* W : m_OwnedWeapons) {
		W->ToggleProjectileSprites();
	}
}

void DirectionalCharacter::ToggleBowTripleShot()
{
	// Toggle rapid attack
	for (Weapon* W : m_OwnedWeapons) {
		if (auto BowTest = dynamic_cast<Bow*>(W)) {
			BowTest->ToggleTripleShot();
		}
	}
}

void DirectionalCharacter::ToggleRapidAttack()
{
	// Toggle rapid attack
	for (Weapon* W : m_OwnedWeapons) {
		W->ToggleRapidAttack();
	}
}

void DirectionalCharacter::OnStart()
{
	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	m_Bounds = AddBounds(0.0f, ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Tag = GetTag();
	m_Bounds->m_TargetTag = GetTargetTag();
	m_Bounds->m_Debug = false;
}

void DirectionalCharacter::OnProcessInput(Input* GameInput)
{
	Super::OnProcessInput(GameInput);
}

void DirectionalCharacter::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Get the directional character idle state
	// idle = true, moving = false
	bool IdleState = (m_MoveDirection.Length() <= 0.0f);

	// Update the last movement direction
	if (m_MoveDirection.x > 0) {
		m_LastMovementDirection = DIRECTION_RIGHT;
	}
	else if (m_MoveDirection.x < 0) {
		m_LastMovementDirection = DIRECTION_LEFT;
	}
	else if (m_MoveDirection.y < 0) {
		m_LastMovementDirection = DIRECTION_UP;
	}
	else if (m_MoveDirection.y > 0) {
		m_LastMovementDirection = DIRECTION_DOWN;
	}

	// Set the directional character animations
	SetAnimation(m_LastMovementDirection, IdleState);
}

void DirectionalCharacter::Cleanup()
{
	// Erase weapons
	for (int i = m_OwnedWeapons.size() - 1; i >= 0; i--) {
		m_OwnedWeapons[i]->DestroyObject();
	}
	m_OwnedWeapons.clear();

	Super::Cleanup();
}

void DirectionalCharacter::CollectGarbage()
{
	// Erase weapons
	std::erase_if(m_OwnedWeapons,
		[](Weapon* W) {
			if (!W->IsPendingDestroy()) {
				return false;
			}

			AW_LOG("DirectionalCharacter", "Erased weapon.");

			return true;
		}
	);

	Super::CollectGarbage();
}

void DirectionalCharacter::OnDeath(GameObject* DeathCauser, bool doDestroy)
{
	// Destroy weapons
	DestroyWeapons();

	// Play vfx
	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_Explosion>();
	VFX->SetPosition(GetTransform().Position);
	VFX->SetScale(m_Scale);

	// Play sfx
	SoundManager::Get().PlaySound(AW_SOUND_DEATH_STANDARD);

	Super::OnDeath(DeathCauser, doDestroy);
}

void DirectionalCharacter::AddWeapon(Weapon* NewWeapon)
{
	NewWeapon->SetOwner(this);

	m_OwnedWeapons.push_back(NewWeapon);
}

void DirectionalCharacter::DestroyWeapons()
{
	// Destroy weapons
	for (const auto Item : m_OwnedWeapons) {

		Item->DestroyObject();

		AW_LOG("DirectionalCharacter", "Destroyed weapon.");
	}
}

void DirectionalCharacter::Attack(Vector2 TargetPosition, bool AttackCondition)
{
	if (m_OwnedWeapons.empty()) {
		return;
	}

	// Attack with used weapon
	m_OwnedWeapons.at(m_UsedWeapon)->SetTargetPosition(TargetPosition);

	if (AttackCondition && !m_OwnedWeapons.at(m_UsedWeapon)->IsAttacking()) {
		m_OwnedWeapons.at(m_UsedWeapon)->Attack();
	}
}

void DirectionalCharacter::SwitchWeapon(bool ForwardOrBackward)
{
	// Check weapons array size
	if (m_OwnedWeapons.empty()) {
		return;
	}

	// Scroll switch weapon
	if (ForwardOrBackward) {
		// Scroll Forward
		if (++m_UsedWeapon == m_OwnedWeapons.size()) { m_UsedWeapon = 0; }
	}
	else {
		// Scroll Backward
		if (--m_UsedWeapon == uint32_t(-1)) { m_UsedWeapon = m_OwnedWeapons.size() - 1; }
	}

	// Update weapon states
	UpdateWeaponStates();
}

void DirectionalCharacter::UpdateWeaponStates()
{
	if (m_OwnedWeapons.empty()) {
		return;
	}

	// Set active if used weapon, else set deactive
	for (int OwnedWeapon = 0; OwnedWeapon < m_OwnedWeapons.size(); OwnedWeapon++) {
		m_OwnedWeapons.at(OwnedWeapon)->SetActive(OwnedWeapon == m_UsedWeapon);
	}
}

Vector2 DirectionalCharacter::GetLastMovementDirection()
{
	switch (m_LastMovementDirection) {
		case DIRECTION_RIGHT:
			return Vector2(1.0f, 0.0f);
			break;
		case DIRECTION_LEFT:
			return Vector2(-1.0f, 0.0f);
			break;
		case DIRECTION_UP:
			return Vector2(0.0f, -1.0f);
			break;
		case DIRECTION_DOWN:
			return Vector2(0.0f, 1.0f);
			break;
		default:
			AW_LOG("DirectionalCharacter", "No last movement direction.");
			return Vector2();
	}
}

void DirectionalCharacter::SetAnimation(uint32_t Direction, bool IdleState)
{
	// Check all sprites are not nullptr
	if (m_DirectionSprites.size() > 7) {
		for (int Sprite = 0; Sprite < 8; Sprite++) {
			if (m_DirectionSprites[Sprite] == nullptr) {
				return;
			}
		}
	}

	// Set all direction sprites (idle and moving) to inactive
	for (int Sprite = 0; Sprite < 8; Sprite++) {
		m_DirectionSprites[Sprite]->SetActive(false);
	}

	// Activate the correct direction sprite (idle and moving)
	// + 4 when the idle state is false (moving) to get the latter moving sprites
	m_DirectionSprites[Direction + !IdleState * 4]->SetActive(true);
}

void DirectionalCharacter::ScreenWrap(float HalfSpriteSize)
{
	// Screen wrap the directional character
	float ScreenHeight = Game::GetGame()->WindowHeightF();
	float ScreenWidth = Game::GetGame()->WindowWidthF();

	// Bottom to top
	if (GetTransform().Position.y - HalfSpriteSize > ScreenHeight) {
		SetPosition({ GetTransform().Position.x, -HalfSpriteSize });
	}
	// Top to bottom
	if (GetTransform().Position.y + HalfSpriteSize < -HalfSpriteSize) {
		SetPosition({ GetTransform().Position.x, ScreenHeight + HalfSpriteSize });
	}
	// Right to left
	if (GetTransform().Position.x - HalfSpriteSize > ScreenWidth) {
		SetPosition({ -HalfSpriteSize, GetTransform().Position.y });
	}
	// Left to right
	if (GetTransform().Position.x + HalfSpriteSize < -HalfSpriteSize) {
		SetPosition({ ScreenWidth + HalfSpriteSize, GetTransform().Position.y });
	}
}

void DirectionalCharacter::ScreenBorder(float HalfSpriteSize)
{
	// Screen border the directional character
	float ScreenHeight = Game::GetGame()->WindowHeightF();
	float ScreenWidth = Game::GetGame()->WindowWidthF();

	// Bottom to top
	if (GetTransform().Position.y + HalfSpriteSize > ScreenHeight) {
		SetPosition({ GetTransform().Position.x, ScreenHeight - HalfSpriteSize });
	}
	// Top to bottom
	if (GetTransform().Position.y - HalfSpriteSize < 0) {
		SetPosition({ GetTransform().Position.x, HalfSpriteSize });
	}
	// Right to left
	if (GetTransform().Position.x + HalfSpriteSize > ScreenWidth) {
		SetPosition({ ScreenWidth - HalfSpriteSize, GetTransform().Position.y });
	}
	// Left to right
	if (GetTransform().Position.x - HalfSpriteSize < 0) {
		SetPosition({ HalfSpriteSize, GetTransform().Position.y });
	}
}