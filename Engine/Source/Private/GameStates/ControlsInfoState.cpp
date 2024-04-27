#include "GameStates/ControlsInfoState.h"

#include "GameObjects/TextObject.h"

#include "Game.h"
#include "Input.h"

void ControlsInfoState::OnStart()
{
	// Add objects
	m_Background = AddGameObject<Background>();
	m_Background->SetBackgroundSprite("Content/NinjaAdventure/Custom Background/Background_MainMenuState.png");
	m_Background->SetPosition({
		Game::GetGame()->WindowWidthF() / 2.0f,
		Game::GetGame()->WindowHeightF() / 2.0f }
	);
	m_Background->SetScale(1.0f);

	float HalfWidth = Game::GetGame()->WindowWidthF() / 2.0f;
	float HalfHeight = Game::GetGame()->WindowHeightF() / 2.0f;

	float TitleOffset = HalfHeight / 1.5f;
	m_TitleText = AddGameObject<TextObject>();
	m_TitleText->SetAligment(AL_CENTER);
	m_TitleText->SetPosition(Vector2(HalfWidth, HalfHeight - TitleOffset));
	m_TitleText->SetFontSize(60);
	m_TitleText->SetText("RUINS OF OBLIVION");

	float SubTitleOffset = HalfHeight / 5.0f;
	float BaseOffset = HalfHeight * 1.25f;

	TextObject* Text1 = AddGameObject<TextObject>();
	Text1->SetAligment(AL_CENTER);
	Text1->SetPosition(Vector2(HalfWidth, BaseOffset - SubTitleOffset * 3));
	Text1->SetFontSize(25);
	Text1->SetText("SEE THE CONTROLS IN THE FILE VIEWER!");

	TextObject* Text2 = AddGameObject<TextObject>();
	Text2->SetAligment(AL_CENTER);
	Text2->SetPosition(Vector2(HalfWidth, BaseOffset - SubTitleOffset));
	Text2->SetFontSize(25);
	Text2->SetText("KEEP KILLING ENEMIES YOU FIND A KEY!");

	TextObject* Text3 = AddGameObject<TextObject>();
	Text3->SetAligment(AL_CENTER);
	Text3->SetPosition(Vector2(HalfWidth, BaseOffset));
	Text3->SetFontSize(25);
	Text3->SetText("AFTER COLLECTING IT, EXIT THROUGH THE CAVE!");

	TextObject* Text4 = AddGameObject<TextObject>();
	Text4->SetAligment(AL_CENTER);
	Text4->SetPosition(Vector2(HalfWidth, BaseOffset + SubTitleOffset));
	Text4->SetFontSize(25);
	Text4->SetText("YOU CAN BLOCK ENEMY ATTACKS WITH YOUR OWN!");

	m_QuitText = AddGameObject<TextObject>();
	m_QuitText->SetAligment(AL_CENTER);
	m_QuitText->SetPosition(Vector2(HalfWidth, BaseOffset + SubTitleOffset * 3));
	m_QuitText->SetFontSize(45);
	m_QuitText->SetText("MENU - M");
}

void ControlsInfoState::OnProcessInput(Input* GameInput)
{
	if (GameInput->IsKeyDown(AW_KEY_M)) {
		if (m_PauseTimer <= 0.0f) {
			Game::GetGame()->GetGameStateMachine()->SetNewGameState(new MainMenuState);
		}
	}
}

void ControlsInfoState::OnCleanup()
{
	m_TitleText->DestroyObject();
	m_QuitText->DestroyObject();
}
