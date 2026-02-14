#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_ArrowMiss : public VisualEffectObject {
public:
	VFX_ArrowMiss() {
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.EndFrame = 3;
		AnimParams.MaxFrames = 4;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Circle/SpriteSheetWhite.png",
			false,
			&AnimParams
		);
	}
};