#include "GameObjects/SpriteObject.h"

void SpriteObject::Cleanup()
{
	for (auto Sprite : m_SpriteStack) {
		delete Sprite;
		Sprite = nullptr;
	}
}

Animation* SpriteObject::AddSprite(const char* PathToFile, AnimationParams* Params)
{
	Animation* NewAnim = new Animation();

	if (!NewAnim->CreateAnimation(PathToFile, Params)) {
		return nullptr;
	}
	
	// Set the sprites positition to match the sprite object
	NewAnim->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
	// Set the sprites rotation to match the sprite object
	NewAnim->SetRotation(GetTransform().Rotation);
	// Set the sprites scale to match the sprite object
	NewAnim->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);

	m_SpriteStack.push_back(NewAnim);

	return NewAnim;
}

void SpriteObject::OnPostUpdate(float DeltaTime)
{
	// Loop through each sprite and set it to match the objects transform
	for (auto Sprite : m_SpriteStack) {
		if (Sprite == nullptr) {
			continue;
		}

		// Set the sprites positition to match the sprite object
		Sprite->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
		// Set the sprites rotation to match the sprite object
		Sprite->SetRotation(GetTransform().Rotation);
		// Set the sprites scale to match the sprite object
		Sprite->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);
	}
}
