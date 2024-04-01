#pragma once
#include "Graphics/Texture.h"

typedef struct _TTF_Font TTF_Font;
struct SDL_Color;

class Text : public Texture {
public:
	Text(SDL_Renderer* Renderer);

	virtual bool ImportTexture(const char* PathToFile) override;

	virtual void Cleanup() override;

	// Change the text of the text
	void SetText(const char* NewText);

	// Change the size of the text
	void SetFontSize(int NewSize);

	// Chang ethe color of the font
	void SetFontColor(SDL_Color Color);

protected:
	void UpdateFont();

private:
	// TTF font
	TTF_Font* m_Font;

	// Color of the font
	SDL_Color* m_TextColor;
	
	// Text to render using the font
	const char* m_Text;

	// Size of the font
	int m_FontSize;
};