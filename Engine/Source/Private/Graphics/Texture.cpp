#include "Graphics/Texture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Debug.h"

Texture::Texture(SDL_Renderer* Renderer)
{
	// Initalise Member Variabless
	m_RendererRef = Renderer;
	m_Angle = 0.0f;
	m_Path = "";
	m_PosX = m_PosY = 0;
	m_ScaleX = m_ScaleY = 1.0f;
	m_SurfaceData = nullptr;
	m_TextureRef = nullptr;
	m_ClipRect = nullptr;
	m_IsVisible = true;
}

Texture::~Texture()
{
	if (m_ClipRect != nullptr)
	{
		delete m_ClipRect;
	}
}

bool Texture::ImportTexture(const char* PathToFile)
{
	// Store the path
	m_Path = PathToFile;
	
	// Import the image and convert it to a surface
	// Fill in the object with the data for the image
	m_SurfaceData = IMG_Load(PathToFile);

	// Check if the import failed
	if (m_SurfaceData == nullptr)
	{
		AW_LOG("Texture", "Image failed to import: " << SDL_GetError());

		return false;
	}

	// Create the texture from the surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);

	// Check if the conversion failed
	if (m_TextureRef == nullptr)
	{
		AW_LOG("Texture", "Image conversion to textured failed: " << SDL_GetError());

		Cleanup();
		return false;
	}

	AW_LOG("Texture", "Successfully imported texture: " << m_Path);
	
	return true;
}

void Texture::CopyTexture(Texture* CopyTexture)
{
	m_Path = CopyTexture->m_Path;
	m_SurfaceData = CopyTexture->m_SurfaceData;
	m_TextureRef = CopyTexture->m_TextureRef;
}

void Texture::Draw()
{
	if (!m_IsVisible) {
		return;
	}
	
	float ImageWidth = (float)m_SurfaceData->w;
	float ImageHeight = (float)m_SurfaceData->h;

	SDL_FRect DestRect = {
		(float)m_PosX,
		(float)m_PosY,
		ImageWidth * m_ScaleX,
		ImageHeight * m_ScaleY
	};

	// If we have a set clip then update the width and height of the texture
	if (m_ClipRect != nullptr)
	{
		DestRect.w = m_ClipRect->w * m_ScaleX;
		DestRect.h = m_ClipRect->h * m_ScaleY;
	}

	// Move the texture to be centered at the middle point of the image
	DestRect.x -= DestRect.w / 2;
	DestRect.y -= DestRect.h / 2;

	SDL_FPoint Center {
		DestRect.w / 2,
		DestRect.h / 2
	};
	
	SDL_RenderCopyExF(
		m_RendererRef,	// Renderer to draw to
		m_TextureRef,	// Texture to draw to renderer
		m_ClipRect,		// Clip rect
		&DestRect,		// Position and scale on the screen
		m_Angle,		// Rotation of the texture
		&Center,		// Center point for rotation
		SDL_FLIP_NONE	// Flip the texture vertical or horizontal
	);
}

void Texture::Cleanup()
{
	// Cleanup the surface
	if (m_SurfaceData != nullptr)
	{
		SDL_FreeSurface(m_SurfaceData);
	}

	// Cleanup the texture
	if (m_TextureRef != nullptr)
	{
		SDL_DestroyTexture(m_TextureRef);
	}

	AW_LOG("Texture", "Successfully destroyed image: " << m_Path);
}

void Texture::SetClip(int x, int y, int w, int h)
{
	if (m_ClipRect == nullptr)
	{
		// Create the SDL Rect object
		m_ClipRect = new SDL_Rect();
	}

	// Set the Clip Rect values
	m_ClipRect->x = x;
	m_ClipRect->y = y;
	m_ClipRect->w = w;
	m_ClipRect->h = h;
}