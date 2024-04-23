#include "GameObjects/PlayerProjectile.h"

PlayerProjectile::PlayerProjectile()
{
	m_TargetTag = "ENEMY";
	m_Size = 23.0f;
	m_Scale = 1.3f;

	m_MaxSpeed = 750.0f;

	// Main sprite
	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 23;
	AnimParams.FrameWidth = 23;
	AnimParams.EndFrame = 1;
	AnimParams.MaxFrames = 2;

	m_MainSprite = AddSprite(
		"Content/NinjaAdventure/FX/Projectile/BigShuriken.png",
		&AnimParams
	);

	// Set the scale
	SetScale(m_Scale);

	m_Bounds->SetBoundsExtent(ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
	m_Bounds->m_Debug = false;
}
