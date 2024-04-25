#pragma once
#include "GameObjects/VisualEffectObject.h"

class VFX_ArrowHit : public VisualEffectObject {
public:
	VFX_ArrowHit() {
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.EndFrame = 3;
		AnimParams.MaxFrames = 4;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Circle/SpriteSheetWhite.png",
			&AnimParams
		);
	}
};