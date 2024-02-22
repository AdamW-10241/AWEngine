#include "Graphics/Animation.h"
#include "Game.h"
#include "Debug.h"
#include "Graphics/Texture.h"

Animation::Animation()
{
	m_TextureRef = nullptr;
	m_AnimParams = nullptr;
	m_CurrentFrame = 0;
	m_FrameTimer = 0.0f;
}

Animation::~Animation()
{
	if (m_AnimParams != nullptr)
	{
		delete m_AnimParams;
	}
	
	if (m_TextureRef != nullptr)
	{
		Game::GetGame()->DestroyTexture(m_TextureRef);
	}
}

bool Animation::CreateAnimation(const char* PathToFile, AnimationParams* Params)
{
	m_TextureRef = Game::GetGame()->ImportTexture(PathToFile);

	// If the import failed
	if (m_TextureRef == nullptr)
	{
		AW_LOG("Animation", "Animation failed to import texture: " << PathToFile);
		return false;
	}

	// Set the parameters
	m_AnimParams = Params;
	// If animation parameters were set
	if (m_AnimParams != nullptr)
	{
		m_CurrentFrame = m_AnimParams->StartFrame;

		// Update the clip to start on the first frame
		m_TextureRef->SetClip(
			m_AnimParams->ClipX + (m_AnimParams->FrameWidth * m_CurrentFrame),
			m_AnimParams->ClipY,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);
	}

	return true;
}

void Animation::Update(float DeltaTime)
{
	if (m_AnimParams == nullptr || m_AnimParams->fps == 0)
	{
		return;
	}

	// Increase the frame timer each frame to get time passed
	m_FrameTimer += DeltaTime;

	// Check if the frame timer has reached the time to update to the next frame
	if (m_FrameTimer >= 1.0f / m_AnimParams->fps)
	{
		m_CurrentFrame++;

		if (m_CurrentFrame > m_AnimParams->EndFrame)
		{
			// Set to Start Frame
			m_CurrentFrame = m_AnimParams->StartFrame;
		}

		// Update the clip to start on the next frame
		m_TextureRef->SetClip(
			m_AnimParams->ClipX + (m_AnimParams->FrameWidth * m_CurrentFrame),
			m_AnimParams->ClipY,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);

		// Reset the timer so we can go to the next frame of animation
		m_FrameTimer = 0.0f;
	}
}

void Animation::SetPosition(int x, int y)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_PosX = x;
	m_TextureRef->m_PosY = y;
}

void Animation::SetRotation(float Angle)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_Angle = Angle;
}

void Animation::SetScale(float Scale)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_Scale = Scale;
}

void Animation::MoveXBetween(float StartX, float EndX, float TimeToMoveBetween, float DeltaTime)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	// Change Direction Of Sprite and Movement
	if (m_TextureRef->m_PosX > EndX)
	{
		m_TextureRef->m_FlipHorizontally = true;
	}
	else if (m_TextureRef->m_PosX < StartX)
	{
		m_TextureRef->m_FlipHorizontally = false;
	}

	// Change movement direction based on the horizontal flip status
	signed int FlipStatusMultiplier = (m_TextureRef->m_FlipHorizontally == false) ? 1 : -1;

	// Move sprite between the start and end x values
	// Take the set amount of time To move between the x values
	m_TextureRef->m_PosX += (EndX - StartX) * DeltaTime / TimeToMoveBetween * FlipStatusMultiplier;
}

void Animation::Rotate(float TimeToRotate, float DeltaTime)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	// Rotate Animation
	m_TextureRef->m_Angle += 360 * DeltaTime / TimeToRotate;
}
