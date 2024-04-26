#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_ArrowHit : public VisualEffectObject {
public:
	VFX_ArrowHit() {
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.EndFrame = 5;
		AnimParams.MaxFrames = 6;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Circle/SpriteSheetSpark.png",
			&AnimParams
		);
	}
};