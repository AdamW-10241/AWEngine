#include "GameObjects/Weapons/Bow.h"
#include "GameObjects/DirectionalCharacter.h"
#include "GameObjects/Weapons/Arrow.h"

#include "Game.h"
#include "SDL2/SDL_mixer.h"

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

	// Load sound effects
	// Arrow hit sound
	m_W_SFX[W_SFX_HIT] = Mix_LoadWAV("Content/Audio/HIT_SFX_Bow.wav");
	// Arrow miss sound
	m_W_SFX[W_SFX_MISS] = Mix_LoadWAV("Content/Audio/MISS_SFX_Bow.wav");

	for (auto SFX : m_W_SFX) {
		if (SFX != nullptr) {
			Mix_VolumeChunk(SFX, 100);
		}
	}
}

void Bow::OnAttack()
{
	// Spawn Arrow
	SpawnArrow();

	// Set the cooldown timer
	Cooldown();
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
	Arrow* SpawnedArrow = Game::GetGame()->AddGameObject<Arrow>(m_Scale);

	// Adjust the arrow
	SpawnedArrow->SetupProjectile(this, m_Damage);
	SpawnedArrow->SetPosition(GetTransform().Position + m_MainSprite->m_Offset.Position);
	SpawnedArrow->SetRotation(m_MainSprite->m_Offset.Rotation - m_RotationOffset);

	SpawnedArrow->FireProjectile();
}