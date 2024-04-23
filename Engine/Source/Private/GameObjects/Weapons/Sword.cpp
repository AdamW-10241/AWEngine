#include "GameObjects/Weapons/Sword.h"

#include "Debug.h"

#define Super Weapon

Sword::Sword(float DifficultyScale)
{
	// Set variables
	m_Damage = 1.0f;
	m_Damage *= DifficultyScale;

	m_Scale = 3.0f;
	m_Size = 10.0f;

	// Main sprite
	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/Items/Weapons/Sword2/Sprite.png"
	);

	// Set the scale
	SetScale(m_Scale);

	// Add bounds
	Bounds* SwordBounds = AddBounds(0.0f, ScaledSize());
	SwordBounds->m_OriginOffset = -ScaledHalfSize();
	SwordBounds->m_Tag = "WEAPON";
	SwordBounds->m_Debug = true;
}

void Sword::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	//
}

void Sword::OnAttack()
{
	AW_LOG("Sword", GetTransform().Position.x);
}
