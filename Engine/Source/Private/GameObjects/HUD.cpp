#include "GameObjects/HUD.h"

#include "GameObjects/TextObject.h"
#include "GameObjects/Player.h"

#include "Game.h"
#include <string>
#include <iomanip>
#include <sstream>

HUD::HUD(Player* PlayerRef)
{
	m_PlayerRef = PlayerRef;
	
	SetPosition(Game::GetGame()->GetScreenCenter());

	m_ScoreText = Game::GetGame()->AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ Game::GetGame()->WindowWidthF() - 10.0f, 20.0f});
	m_ScoreText->SetFontSize(24);
	m_ScoreText->SetAligment(AL_TOP_RIGHT);
	m_CurrentScore = -1;
	UpdateScore();

	m_PlayerHealthText = Game::GetGame()->AddGameObject<TextObject>();
	m_PlayerHealthText->SetPosition({ 20.0f, 20.0f });
	m_PlayerHealthText->SetFontSize(30);
	m_PlayerHealthText->SetAligment(AL_TOP_LEFT);
	m_MaxHealth = m_PlayerRef->GetMaxHealth();
	m_CurrentHealth = -1.0f;
	UpdateHealth();

	m_DashText = Game::GetGame()->AddGameObject<TextObject>();
	m_DashText->SetPosition({ 20.0f, 60.0f });
	m_DashText->SetFontSize(20);
	m_DashText->SetAligment(AL_TOP_LEFT);
	m_BaseDash = m_PlayerRef->GetBaseDash();
	m_CurrentDash = -1.0f;
	UpdateDash();
	
	SetVisibleText(true);

	// Add sprite
	m_MainSprite = AddSprite(
		"Content/CustomHUD.png",
		true
	);
}

void HUD::SetVisibleText(bool State)
{
	if (State) {
		m_ScoreText->SetFontColor(255, 255, 255, 255);
		m_PlayerHealthText->SetFontColor(242, 45, 45, 255);
		m_DashText->SetFontColor(69, 158, 141, 255);
		return;
	}

	m_ScoreText->SetFontColor(0, 0, 0, 1);
	m_PlayerHealthText->SetFontColor(0, 0, 0, 1);
	m_DashText->SetFontColor(0, 0, 0, 1);
}

void HUD::OnUpdate(float DeltaTime)
{
	// Update
	UpdateHealth();
	UpdateDash();
	UpdateScore();
}

void HUD::UpdateScore()
{
	int Score = std::min(Game::GetGame()->m_Score, 999999);

	if (Score == m_CurrentScore) {
		return;
	}

	// Update score
	m_CurrentHealth = Score;

	// Use a stream to set float text precision
	std::stringstream stream;
	stream << std::fixed << Score;

	std::string ScoreString = stream.str();
	m_ScoreText->SetText(ScoreString.c_str());
}

void HUD::UpdateHealth()
{
	float Health = m_PlayerRef->GetHealth();

	if (Health == m_CurrentHealth) {
		return;
	}

	// Update health
	m_CurrentHealth = Health;

	int HealthPercentage = int(100.0f * m_CurrentHealth / m_MaxHealth);

	// Use a stream
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << HealthPercentage << "%";

	std::string HealthString = stream.str();
	m_PlayerHealthText->SetText(HealthString.c_str());
}

void HUD::UpdateDash()
{
	float Dash = m_PlayerRef->GetCurrentDash();

	if (Dash == m_CurrentDash) {
		return;
	}

	// Update health
	m_CurrentDash = Dash;

	int DashPercentage = int(100 - 100.0f * m_CurrentDash / m_BaseDash);

	// Use a stream
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << DashPercentage << "%";

	std::string DashString = stream.str();
	m_DashText->SetText(DashString.c_str());
}
