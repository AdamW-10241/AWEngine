#pragma once

// Forward Declaration
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture();

	// Import and create a texture
	bool ImportTexture(const char* PathToFile);
	// Copy the texture
	void CopyTexture(Texture* CopyTexture);
	// Draw the texture to the renderer
	void Draw();
	// Deallocate memory
	void Cleanup();
	// Get the original image path
	const char* GetPath() const { return m_Path; }
	// Set the clip for the texture
	void SetClip(int x, int y, int w, int h);

public:
	// Position X & Y to render to
	int m_PosX, m_PosY;

	// Rotation of the image
	float m_Angle;

	// Scale the texture
	float m_ScaleX, m_ScaleY;

private:
	// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store the assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;

	// Path to original image
	const char* m_Path;

	// Store the clip for the texture
	SDL_Rect* m_ClipRect;
};