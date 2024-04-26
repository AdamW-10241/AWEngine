#pragma once
#include "GameObjects/Character.h"
#include "GameObjects/VFX/VisualEffectObject.h"

#include "Game.h"

struct Mix_Chunk;

class Collectable : public Character {
public:
	Collectable();

protected:
	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;
	
	virtual void CollectCollectable() {};

	virtual void PlayFX() {};

	template<class T, std::enable_if_t<std::is_base_of_v<VisualEffectObject, T>, T>* = nullptr>
	void OnPlayFX() {
		const auto VFX = Game::GetGame()->Game::AddGameObject<T>();
		VFX->SetPosition(GetTransform().Position);
		VFX->SetScale(m_Scale * 0.5f);
	}

protected:
	// Collectable score value
	float m_ScoreValue;
};