#pragma once
#include "GameObjects/Character.h"
#include "GameObjects/VFX/VisualEffectObject.h"

#include "Game.h"

struct Mix_Chunk;

class Collectable : public Character {
public:
	Collectable();

protected:
	virtual void OnStart();

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
	
	virtual void CollectCollectable() {};

	virtual void PlayFX() {};

	template<class T, std::enable_if_t<std::is_base_of_v<VisualEffectObject, T>, T>* = nullptr>
	void OnPlayFX(float Scale = 1.0f) {
		const auto VFX = Game::GetGame()->Game::AddGameObject<T>();
		VFX->SetPosition(GetTransform().Position);
		VFX->SetScale(Scale);
	}

protected:
	// Collectable score value
	float m_ScoreValue;
};