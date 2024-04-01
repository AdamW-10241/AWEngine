#include "GameObjects/TextObject.h"
#include "Game.h"
#include "Graphics/Text.h"
#include "SDL2/SDL.h"

#define Super GameObject

TextObject::TextObject(const char* PathToFile)
{
	m_Text = Game::GetGame()->ImportText(PathToFile);
}

void TextObject::SetText(const char* NewText)
{
	m_Text->SetText(NewText);
}

void TextObject::SetFontSize(int NewSize)
{
	m_Text->SetFontSize(NewSize);
}

void TextObject::SetFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_Text->SetFontColor({ r, g, b, a });
}

void TextObject::SetAligment(EAlignment NewAlignment)
{
	m_Text->m_Alignment = NewAlignment;
}

void TextObject::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	// Matching the text to the position of the game object
	m_Text->m_PosX = GetTransform().Position.x;
	m_Text->m_PosY = GetTransform().Position.y;

	// Match the text rotation to the game object
	m_Text->m_Angle = GetTransform().Rotation;
}

void TextObject::Cleanup()
{
	if (m_Text != nullptr) {
		Game::GetGame()->DestroyText(m_Text);
	}

	Super::Cleanup();
}
