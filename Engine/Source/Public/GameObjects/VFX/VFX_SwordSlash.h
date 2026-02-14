#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_SwordSlash : public VisualEffectObject {
public:
	VFX_SwordSlash() {
		AnimationParams AnimParams;
		AnimParams.fps = 12;
		AnimParams.EndFrame = 3;
		AnimParams.MaxFrames = 4;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/SlashFx/SlashDouble/SpriteSheet.png",
			false,
			&AnimParams
		);
	}
};