#include "GameObjects/PlayerProjectile.h"

PlayerProjectile::PlayerProjectile()
{
	m_TargetTag = "ENEMY";

	AnimationParams AnimParams;
	AnimParams.fps = 24;
	AnimParams.FrameHeight = 32;
	AnimParams.FrameWidth = 32;
	AnimParams.EndFrame = 9;
	AnimParams.MaxFrames = 10;

	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship Weapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
		&AnimParams
	);

	m_Size = 32.0f;
	m_Scale = 2.0f;
	SetScale(m_Scale);

	m_Bounds->SetBoundsExtent(ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
}
