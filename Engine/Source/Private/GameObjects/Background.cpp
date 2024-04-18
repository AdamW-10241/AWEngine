#include "GameObjects/Background.h"

void Background::SetBackgroundSprite(const char* PathToFile)
{
	if (m_MainSprite == nullptr) {
		m_MainSprite = AddSprite(PathToFile);
	}
}