#include "Menus/WinMenu.h"

#include <Windows.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_messagebox.h"
#include "resource.h"

#include "Debug.h"

WinMenu::WinMenu(SDL_Window* Window)
{
	// Assign the window menu
	m_Window = Window;

	// Get the sdl version and add it to the window info
	SDL_VERSION(&m_WindowInfo.version);

	// After version assingment we can now get the correct window info
	// Must already have version set
	SDL_GetWindowWMInfo(m_Window, &m_WindowInfo);
}

bool WinMenu::InitialiseMenu()
{
	// Convert our SDL window info to a windows version
	HWND SysWMInfo = m_WindowInfo.info.win.window;

	// Get the resource
	// GetModuleHandle(0) gets the current active window instance
	HINSTANCE WindowInstance = GetModuleHandle(0);

	// MAKEINTRESOURCE converts the created menu into a string
	// Selected menu
	LPCWSTR VSMenuString = MAKEINTRESOURCE(IDR_MENU1);

	// Load the selected menu into the chosen instance
	HMENU SysMenu = LoadMenu(WindowInstance, VSMenuString);

	// Apply the windows menu to SDL
	if (!SetMenu(SysWMInfo, SysMenu)) {
		AW_LOG("WinMenu", "Windows could not assign the menu.");
		return false;
	}

	// Activate a listener for the window menus in SDL
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	return true;
}

void WinMenu::ActivatePopup(const char* Title, const char* Msg)
{
	// Create a windows menu popup through SDL
	// SDL_ShowMessageBox (different)
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_INFORMATION,
		Title,
		Msg,
		m_Window
	);
}

void WinMenu::ActivatePopupWarning(const char* Title, const char* Msg)
{
	// Create a windows menu popup through SDL
	// SDL_ShowMessageBox (different)
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_WARNING,
			Title,
			Msg,
			m_Window
		);
}
