#include "GameObjects/SpriteObject.h"
#include "Debug.h"

#define Super GameObject

void SpriteObject::Cleanup()
{
	for (auto Sprite : m_SpriteStack) {
		delete Sprite;
		Sprite = nullptr;
	}
}

Sprite* SpriteObject::AddSprite(const char* PathToFile, AnimationParams* Params)
{
	Animation* NewAnim = new Animation();

	if (!NewAnim->CreateAnimation(PathToFile, Params)) {
		return nullptr;
	}
	
	Sprite* NewSprite = new Sprite(NewAnim);

	// Set the sprite to the object transforms
	SpriteFollowObject(NewSprite);

	// Add it to the sprite stack
	m_SpriteStack.push_back(NewSprite);

	return NewSprite;
}

void SpriteObject::OnPostUpdate(float DeltaTime)
{
	Super::OnPostUpdate(DeltaTime);
	
	// Loop through each sprite and set it to match the objects transform
	for (auto Sprite : m_SpriteStack) {
		if (Sprite == nullptr) {
			continue;
		}

		// Move the sprite to the location of the object
		SpriteFollowObject(Sprite);

		// Update the sprites animation
		Sprite->m_Sprite->Update(DeltaTime);
	}
}

void SpriteObject::SpriteFollowObject(Sprite* SpriteToFollow)
{
	// Set the sprites positition to match the sprite object
	SpriteToFollow->m_Sprite->SetPosition(
		(int)GetTransform().Position.x + SpriteToFollow->m_Offset.Position.x,
		(int)GetTransform().Position.y + SpriteToFollow->m_Offset.Position.y);

	// Set the sprites rotation to match the sprite object
	SpriteToFollow->m_Sprite->SetRotation(
		GetTransform().Rotation + SpriteToFollow->m_Offset.Rotation);

	// Set the sprites scale to match the sprite object
	SpriteToFollow->m_Sprite->SetScale(
		GetTransform().Scale.x + SpriteToFollow->m_Offset.Scale.x,
		GetTransform().Scale.y + SpriteToFollow->m_Offset.Scale.y);
}
