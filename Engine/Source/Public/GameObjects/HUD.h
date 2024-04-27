#pragma once
#include "GameObjects/Character.h"

class TextObject;
class Player;
class PlayState;

class HUD : public Character{
public:
	HUD(Player* PlayerRef);

	void SetVisibleText(bool State);

protected:
	virtual void OnUpdate(float DeltaTime);

	virtual void UpdateScore();

	virtual void UpdateHealth();

	virtual void UpdateDash();

protected:
	Player* m_PlayerRef;

	TextObject* m_ScoreText;

	int m_CurrentScore;

	TextObject* m_PlayerHealthText;

	float m_MaxHealth;

	float m_CurrentHealth;

	TextObject* m_DashText;

	float m_BaseDash;
	
	float m_CurrentDash;
};