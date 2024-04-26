#pragma once
#include "GameObjects/VisualEffectObject.h"

class VFX_CollectableCollect : public VisualEffectObject {
public:
	VFX_CollectableCollect() {
		AnimationParams AnimParams;
		AnimParams.fps = 24;
		AnimParams.EndFrame = 4;
		AnimParams.MaxFrames = 5;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Spark/SpriteSheet.png",
			&AnimParams
		);
	}
};