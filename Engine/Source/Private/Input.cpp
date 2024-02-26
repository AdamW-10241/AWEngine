#include "Input.h"
#include "SDL2/SDL.h"
#include "Game.h"
#include "Math/Vector2.h"

void Input::ProcessInput()
{
	// Data type that reads SDL window input events
	SDL_Event InputEvent;

	// Run through each input each frame
	while (SDL_PollEvent(&InputEvent)) {
		// Was the input that was pressed a mouse button
		// and is it pressed down
		if (InputEvent.type == SDL_MOUSEBUTTONDOWN) {
			DetectMouseButtonState(InputEvent.button.button, true);
		}
		// Was the input that was pressed a mouse button
		// and was it released
		if (InputEvent.type == SDL_MOUSEBUTTONUP) {
			DetectMouseButtonState(InputEvent.button.button, false);
		}

		// If the window cross is pressed, close the app
		if (InputEvent.type == SDL_QUIT) {
			Game::GetGame()->QuitApp();
		}
	}
}

bool Input::IsKeyDown(AW_Key Key)
{
	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	if (KeyStates == nullptr) {
		return false;
	}

	return KeyStates[Key];
}

bool Input::IsMouseButtonDown(AW_MouseButton Button)
{
	if (Button >= AW_NUM_BUTTONS) {
		return false;
	}

	return m_MouseState[Button];
}

void Input::DetectMouseButtonState(unsigned int Event, bool Value)
{
	switch (Event) {
		case SDL_BUTTON_LEFT:
			m_MouseState[AW_MOUSE_LEFT] = Value;
			break;
		case SDL_BUTTON_MIDDLE:
			m_MouseState[AW_MOUSE_MIDDLE] = Value;
			break;
		case SDL_BUTTON_RIGHT:
			m_MouseState[AW_MOUSE_RIGHT] = Value;
			break;
		default:
			break;
	}
}

Vector2 Input::GetMousePos() const
{
	// Mouse position variables
	int x(0);
	int y(0);

	// This function will change our x and y variables to the mouse location
	SDL_GetMouseState(&x, &y);
	
	return Vector2((float)x, (float)y);
}
