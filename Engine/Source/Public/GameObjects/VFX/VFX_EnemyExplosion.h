#pragma once
#include "GameObjects/VisualEffectObject.h"

class VFX_EnemyExplosion : public VisualEffectObject {
public:
	VFX_EnemyExplosion() {
		AnimationParams AnimParams;
		AnimParams.fps = 150;
		AnimParams.EndFrame = 34;
		AnimParams.MaxFrames = 35;
		AnimParams.FrameWidth = 64;
		AnimParams.FrameHeight = 64;

		AddSprite(
			"Content/Sprites/VFX/FireExplode.png",
			&AnimParams
		);
	}
};