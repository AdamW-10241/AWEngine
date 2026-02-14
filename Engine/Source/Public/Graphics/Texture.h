#pragma once
#include "Graphics/TextureTypes.h"

// Forward Declaration
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	Texture(SDL_Renderer* Renderer, bool IsGUI);
	virtual ~Texture();

	// Import and create a texture
	virtual bool ImportTexture(const char* PathToFile);

	// Copy the texture
	void CopyTexture(Texture* CopyTexture);

	// Draw the texture to the renderer
	void Draw();

	// Deallocate memory
	virtual void Cleanup();

	// Get the original image path
	const char* GetPath() const { return m_Path; }

	// Get whether the texture is GUI
	const bool GetIsGUI() const { return m_IsGUI; }

	// Set the clip for the texture
	void SetClip(int x, int y, int w, int h);

public:
	// Position X & Y to render to
	int m_PosX, m_PosY;

	// Rotation of the image
	float m_Angle;

	// Scale the texture
	float m_ScaleX, m_ScaleY;

	// Determine whether or not to render the texture
	bool m_IsVisible;

	// Adjust the alignment of the texture
	EAlignment m_Alignment;

protected:
	// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store the assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;
	
	// Path to original image
	const char* m_Path;

	// Store whether or not the texture is GUI
	bool m_IsGUI;

	// Store the clip for the texture
	SDL_Rect* m_ClipRect;

private:
	// Initialise texture
	void InitialiseTexture(SDL_Renderer* Renderer, bool IsGUI = false);
};