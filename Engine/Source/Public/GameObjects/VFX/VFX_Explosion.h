#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_Explosion : public VisualEffectObject {
public:
	VFX_Explosion() {
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.EndFrame = 5;
		AnimParams.MaxFrames = 6;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Smoke/Smoke/SpriteSheet.png",
			false,
			&AnimParams
		);
	}
};