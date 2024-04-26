#pragma once
#include "GameObjects/GameObject.h"
#include <cstdint>
#include "Graphics/TextureTypes.h"

class Text;

class TextObject : public GameObject {
public:
	TextObject(const char* PathToFile = "Content/Fonts/Press_Start_2P/PressStart2P-Regular.ttf");

	// Change the text of the text
	void SetText(const char* NewText);

	// Change the size of the text
	void SetFontSize(int NewSize);

	// Change the color of the font
	void SetFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	// Set the alignment of the text
	void SetAligment(EAlignment NewAlignment);
	
protected:
	virtual void OnUpdate(float DeltaTime) override;

	virtual void Cleanup() override;

private:
	// Store the text object
	Text* m_Text;
};