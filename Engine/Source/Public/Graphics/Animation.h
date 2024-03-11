#pragma once

class Texture;

struct AnimationParams {
	AnimationParams() {
		FrameWidth = FrameHeight = 0;
		fps = 0.0f;
		StartFrame = EndFrame = 0;
		MaxFrames = 0;
	}

	// Width and height of each frame
	unsigned int FrameWidth, FrameHeight;

	// Frames per second
	float fps;

	// Start and end frame that the animation will play
	unsigned int StartFrame, EndFrame;

	// Amount of frames in the sprite sheet
	unsigned int MaxFrames;
};

class Animation {
public:
	Animation();
	~Animation();

	// Imports the animation and adds animation data
	bool CreateAnimation(const char* PathToFile, AnimationParams* Params = nullptr);
	
	// Update the animation logic each frame
	void Update(float DeltaTime);

	void SetPosition(int x, int y);

	void SetRotation(float Angle);

	void SetScale(float x, float y);

	// Set the visibility of the animation
	void SetVisible(bool IsVisible);

private:
	// Stores the texture to render
	Texture* m_TextureRef;
	// Store the animation data
	AnimationParams* m_AnimParams;
	// The current playing frame of the animation
	unsigned int m_CurrentFrame;
	// How much time has passed since the last animation frame
	float m_FrameTimer;
}; 