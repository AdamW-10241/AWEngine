#include "GameObjects/Weapons/Sword.h"
#include "GameObjects/DirectionalCharacter.h"
#include "GameObjects/VFX/VFX_SwordSlash.h"

#include "Game.h"
#include "SDL2/SDL_mixer.h"

#include "Debug.h"

#define Super Weapon

Sword::Sword(float DifficultyScale)
{
	// Set variables
	m_Damage = 1.0f;
	m_Damage *= DifficultyScale;

	m_CooldownDuration = 1.0f;
	m_AttackDuration = 0.3f;

	m_RotationOffset = 90.0f;

	m_Scale = 4.0f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Weapons/Sword2/Sprite.png"
	);

	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	float const BoundsScalar = 4.0f;

	m_Bounds = AddBounds(0.0f, ScaledSize() * BoundsScalar);
	m_Bounds->m_OriginOffset = -ScaledHalfSize() * BoundsScalar;
	m_Bounds->m_Tag = "WEAPON";
	m_Bounds->m_Debug = true;

	// Load sound effects
	m_W_SFX[W_SFX_HIT] = Mix_LoadWAV("Content/Audio/HIT_SFX_Sword.wav");

	for (auto SFX : m_W_SFX) {
		if (SFX != nullptr) {
			Mix_VolumeChunk(SFX, 15);
		}
	}
}

void Sword::SetAttackPosition(float RadiusMultiplier)
{
	// Update object position
	Vector2 PlayerPosition = m_Owner->GetTransform().Position;

	SetPosition(PlayerPosition);

	// Update object sprite
	float AngleRatio = 2 * PI * (m_AttackTimer / m_AttackDuration);

	Vector2 TargetPosition = PlayerPosition + Vector2(cosf(AngleRatio), sinf(AngleRatio));

	float RadianAngle = atan2(TargetPosition.y - PlayerPosition.y, TargetPosition.x - PlayerPosition.x);
	float Radius = m_Owner->ScaledHalfSize() * RadiusMultiplier;

	Vector2 OffsetPosition = { cosf(RadianAngle) * Radius, sinf(RadianAngle) * Radius };

	// Apply values to sprite
	for (Sprite* WeaponSprite : GetAllSprites()) {
		WeaponSprite->m_Offset.Position = OffsetPosition;
		WeaponSprite->m_Offset.Rotation = (RadianAngle * 180 / PI) + m_RotationOffset;
	}
}

void Sword::SetAimPosition(float RadiusMultiplier)
{
	// Deactivate bounds
	m_Bounds->m_Active = false;

	Super::SetAimPosition(RadiusMultiplier);
}

void Sword::AttackHit(Character* Char, bool DoDamage)
{
	// Damage opponent if set
	if (DoDamage) {
		Char->ApplyDamage(m_Owner, m_Damage);
	}
	
	// Create hit VFX
	CreateHitVFX((Char->GetTransform().Position + GetTransform().Position) / 2.0f);

	// Play hit SFX
	if (m_W_SFX[W_SFX_HIT] != nullptr) {
		Mix_PlayChannel(-1, m_W_SFX[W_SFX_HIT], 0);
	}

	// Set cooldown timer
	Cooldown();

	// Deactivate bounds
	m_Bounds->m_Active = false;
}

void Sword::CreateHitVFX(Vector2 Position)
{
	// Create hit VFX
	auto VFX = Game::GetGame()->Game::AddGameObject<VFX_SwordSlash>();
	VFX->SetPosition(Position);
	VFX->SetScale(m_Scale);
}

void Sword::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (!IsAttacking()) {
		return;
	}

	if (OverlapBounds->GetOwner() == m_Owner) {
		return;
	}

	// Hit other weapon
	if (auto const OtherWeapon = dynamic_cast<Weapon*>(OverlapBounds->GetOwner())) {
		if (strcmp(OtherWeapon->GetOwner()->GetMainBounds()->m_Tag, HitBounds->m_TargetTag) != 0) {
			return;
		}

		// Make other weapon attack land
		OtherWeapon->AttackHit(this, false);

		// Make this weapon attack land
		AttackHit(OtherWeapon, false);
		return;
	}

	// Hit player / enemy
	if (auto Char = dynamic_cast<DirectionalCharacter*>(OverlapBounds->GetOwner())) {
		if (strcmp(Char->GetMainBounds()->m_Tag, HitBounds->m_TargetTag) != 0) {
			return;
		}

		// Handle attack hit
		AttackHit(Char, true);
	}
}

void Sword::OnAttack()
{
	// Activate bounds
	m_Bounds->m_Active = true;
}
