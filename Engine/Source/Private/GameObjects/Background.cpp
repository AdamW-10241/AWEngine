#include "GameObjects/Background.h"

void Background::SetBackgroundSprite(const char* PathToFile)
{
	m_MainSprite = AddSprite(PathToFile);
}
