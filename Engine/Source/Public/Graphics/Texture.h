#pragma once

// Forward Declaration
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture() = default;

	// Import and create a texture
	bool ImportTexture(const char* PathToFile);
	// Draw the texture to the renderer
	void Draw();
	// Deallocate memory
	void Cleanup();
	// Get the original image path
	const char* GetPath() const { return m_Path; }

public:
	// Position X & Y to render to
	int m_PosX, m_PosY;

	// Rotation of the image
	float m_Angle;

	// Scale the texture
	float m_Scale;

private:
	// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store the assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;

	// Path to original image
	const char* m_Path;
};