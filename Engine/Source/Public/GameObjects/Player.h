#pragma once
#include "GameObjects/DirectionalCharacter.h"

struct Mix_Chunk;

class Player : public DirectionalCharacter {
public:
	Player();

	virtual void Cleanup() override;

protected:
	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnDeath(GameObject* DeathCauser);

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Store sound effects
	Mix_Chunk* m_ShootSFX[1] = { nullptr };

private:
	void ScrollSwitchWeapon(Input* GameInput);
};