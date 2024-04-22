#include "GameObjects/VisualEffectObject.h"

#define Super SpriteObject

VisualEffectObject::VisualEffectObject()
{
	m_Length = 0.0f;
	m_Loops = 0;
	m_LifeTimer = 0.0f;
}

void VisualEffectObject::OnStart()
{
	Super::OnStart();
	
	for (auto Item : GetAllSprites()) {
		float Frames = static_cast<float>(
			std::max(Item->m_Sprite->GetAnimParams()->EndFrame - Item->m_Sprite->GetAnimParams()->StartFrame, 0U)
		);

		float AnimLength = Frames / std::max(Item->m_Sprite->GetAnimParams()->fps, 0.0000001f);

		if (AnimLength > m_Length) {
			m_Length = AnimLength;
		}
	}

	m_LifeTimer = m_Length;
}

void VisualEffectObject::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	LifeTimer(DeltaTime);
}

void VisualEffectObject::LifeTimer(float DeltaTime)
{
	m_LifeTimer -= DeltaTime;

	if (m_LifeTimer <= 0.0f) {
		if (m_Loops > 0) {
			m_Loops--;
			m_LifeTimer = m_Length;
			return;
		}

		DestroyObject();
	}
}
