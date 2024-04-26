#pragma once
#include "GameObjects/VFX/VisualEffectObject.h"

class VFX_CollectCoin : public VisualEffectObject {
public:
	VFX_CollectCoin() {
		AnimationParams AnimParams;
		AnimParams.fps = 12;
		AnimParams.EndFrame = 4;
		AnimParams.MaxFrames = 5;
		AnimParams.FrameWidth = 32;
		AnimParams.FrameHeight = 32;

		AddSprite(
			"Content/NinjaAdventure/FX/Magic/Spark/SpriteSheet.png",
			&AnimParams
		);

		m_VFX_SFX = Mix_LoadWAV("Content/Audio/SFX_Coin.wav");
		m_SFX_Volume = 50;
	}
};