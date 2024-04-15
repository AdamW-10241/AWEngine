#pragma once

#include "SDL2/SDL_syswm.h"

class WinMenu {
public:
	WinMenu(SDL_Window* Window);
	~WinMenu() = default;

	// Create a menu and add it to the SDL window
	bool InitialiseMenu();

	// Create a win menu popup with a title and a message
	// \n to create a new line
	void ActivatePopup(const char* Title, const char* Msg);

	void ActivatePopupWarning(const char* Title, const char* Msg);

private:
	// Store the window the menu is attached to
	SDL_Window* m_Window;

	// Stores info about the windows menu for SDL to read
	SDL_SysWMinfo m_WindowInfo;
};