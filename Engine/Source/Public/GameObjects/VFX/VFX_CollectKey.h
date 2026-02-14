#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_CollectKey : public VisualEffectObject {
public:
	VFX_CollectKey() {
		AnimationParams AnimParams;
		AnimParams.fps = 12;
		AnimParams.EndFrame = 4;
		AnimParams.MaxFrames = 5;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Spirit/SpriteSheetBlue.png",
			false,
			&AnimParams
		);

		m_VFX_SFX = Mix_LoadWAV("Content/Audio/SFX_Key.wav");
		m_SFX_Volume = 128;
	}
};