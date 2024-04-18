#include "GameObjects/PlayerProjectile.h"

PlayerProjectile::PlayerProjectile()
{
	m_AltSprite = false;
	
	m_TargetTag = "ENEMY";
}

void PlayerProjectile::OnStart()
{
	// Add enemy base sprite
	if (m_AltSprite) {
		// Alt
		AnimationParams AnimParams;
		AnimParams.fps = 3;
		AnimParams.FrameHeight = 20;
		AnimParams.FrameWidth = 7;
		AnimParams.EndFrame = 2;
		AnimParams.MaxFrames = 3;

		m_MainSprite = AddSprite("Content/Sprites/Main Ship Weapons/PNGs/Main ship weapon - Projectile - Rocket.png",
			&AnimParams);
		m_Size = 14.0f;
		m_Scale = 4.0f;
	}
	else {
		// Default
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.FrameHeight = 32;
		AnimParams.FrameWidth = 32;
		AnimParams.EndFrame = 9;
		AnimParams.MaxFrames = 10;

		m_MainSprite = AddSprite("Content/Sprites/Main Ship Weapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
			&AnimParams
		);
		m_Size = 32.0f;
		m_Scale = 2.0f;
	}

	// Set scale and bounds
	SetScale(m_Scale);

	m_Bounds->SetBoundsExtent(ScaledSize());
	m_Bounds->m_OriginOffset = -ScaledHalfSize();
}
