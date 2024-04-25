#include "GameObjects/Weapons/Bow.h"
#include "GameObjects/DirectionalCharacter.h"
#include "GameObjects/Weapons/Arrow.h"

#include "Game.h"

#include "Debug.h"

#define Super Weapon

Bow::Bow(float DifficultyScale)
{
	// Set variables
	m_Damage = 1.0f;
	m_Damage *= DifficultyScale;

	m_Arrows = 1;

	m_CooldownDuration = 1.5f;
	m_AttackDuration = 0.3f;

	m_RotationOffset = -90.0f;

	m_Scale = 3.0f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Weapons/Bow/Sprite.png"
	);

	// Set the scale
	SetScale(m_Scale);
}

void Bow::OnAttack()
{
	// Spawn Arrow
	SpawnArrow();

	// Set cooldown timer
	m_CooldownTimer = m_CooldownDuration;

	// Play sound effect ???
	//int SoundIndex = 0; // rand() % 3;

	//if (m_ShootSFX[SoundIndex] != nullptr) {
	//	Mix_PlayChannel(-1, m_ShootSFX[SoundIndex], 0);
	//}
}

void Bow::SetIdlePosition(float RadiusMultiplier)
{
	// Make the bow move closer / futher based on time until next fire
	float Offset = 0.5f * (m_CooldownTimer / m_CooldownDuration);

	SetAimPosition(RadiusMultiplier - Offset);
}

void Bow::SpawnArrow()
{
	// Spawning the game object / projectile
	Arrow* SpawnedArrow = Game::GetGame()->AddGameObject<Arrow>();

	// Adjust the arrow
	SpawnedArrow->SetupProjectile(m_Owner, m_Damage);
	SpawnedArrow->SetPosition(GetTransform().Position + m_MainSprite->m_Offset.Position);
	SpawnedArrow->SetRotation(m_MainSprite->m_Offset.Rotation - m_RotationOffset);

	SpawnedArrow->FireProjectile();
}