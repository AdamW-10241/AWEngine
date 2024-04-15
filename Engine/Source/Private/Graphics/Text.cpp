#include "Graphics/Text.h"
#include "SDL2/SDL_ttf.h"
#include "Debug.h"

#define Super Texture

Text::Text(SDL_Renderer* Renderer) : Super(Renderer)
{
	m_Font = nullptr;
	m_TextColor = new SDL_Color({ 255, 255, 255, 255 });
	m_Text = "Text";
	m_FontSize = 24;
}

bool Text::ImportTexture(const char* PathToFile)
{
	// Store the path
	m_Path = PathToFile;

	// Import the font
	m_Font = TTF_OpenFont(PathToFile, m_FontSize);

	// Check if the import failed
	if (m_Font == nullptr) {
		AW_LOG("Text", "Font failed to import: " << TTF_GetError());

		return false;
	}

	// Import the image and convert it to a surface
	// Fill in the object with the data for the image
	m_SurfaceData = TTF_RenderText_Solid(m_Font, m_Text, *m_TextColor);

	// Check if the import failed
	if (m_SurfaceData == nullptr) {
		AW_LOG("Text", "Font failed to convert to surface: " << TTF_GetError());
		Cleanup();

		return false;
	}

	// Create the texture from the surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);

	// Check if the conversion failed
	if (m_TextureRef == nullptr) {
		AW_LOG("Text", "Font conversion to texture failed: " << SDL_GetError());

		Cleanup();
		return false;
	}

	AW_LOG("Text", "Successfully imported font: " << m_Path);

	return true;
}

void Text::Cleanup()
{	
	// Remove the font from memory
	TTF_CloseFont(m_Font);

	Super::Cleanup();
}

void Text::SetText(const char* NewText)
{
	if (NewText == m_Text) {
		return;
	}
	
 	m_Text = NewText;

	UpdateFont();
}

void Text::SetFontSize(int NewSize)
{
	if (m_FontSize == NewSize) { 
		return;
	}

	m_FontSize = NewSize;

	TTF_CloseFont(m_Font);

	m_Font = TTF_OpenFont(m_Path, m_FontSize);

	UpdateFont();
}

void Text::SetFontColor(SDL_Color Color)
{
	if (m_TextColor == &Color) {
		return;
	}

	m_TextColor->r = Color.r;
	m_TextColor->g = Color.g;
	m_TextColor->b = Color.b;
	m_TextColor->a = Color.a;

	UpdateFont();
}

void Text::UpdateFont()
{
	if (m_Font == nullptr) {
		return;
	}

	// Clear the surface data
	SDL_FreeSurface(m_SurfaceData);

	// Delete the texture
	SDL_DestroyTexture(m_TextureRef);

	// Import the image and convert it to a surface
	// Fill in the object with the data for the image
	m_SurfaceData = TTF_RenderText_Solid(m_Font, m_Text, *m_TextColor);

	// Create the texture from the surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);
}
