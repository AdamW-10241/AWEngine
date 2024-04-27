#include "Input.h"

#include "SDL2/SDL.h"
#include "Game.h"
#include "Math/Vector2.h"
#include "SDL2/SDL_syswm.h"
#include "Menus/WinMenu.h"
#include "resource.h"
#include "GameObjects/Player.h"

void Input::ProcessInput()
{
	// Data type that reads SDL window input events
	SDL_Event InputEvent;

	// Reset scroll amount
	m_ScrollAmount = 0;

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

		if (InputEvent.type == SDL_MOUSEWHEEL) {
			m_ScrollAmount = InputEvent.wheel.y;
		}

		// If the window cross is pressed, close the app
		if (InputEvent.type == SDL_QUIT) {
			Game::GetGame()->QuitApp();
		}

		// Listen for windows menu events
		if (InputEvent.type == SDL_SYSWMEVENT) {
			HandleWinMenuEvents(&InputEvent);
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

void Input::HandleWinMenuEvents(SDL_Event* Event)
{
	// Listening to the event message that was passed in
	// if it was a system win menu message (i.e. we pressed a win menu button)
	// then run if case is true
	switch (Event->syswm.msg->msg.win.wParam)
	{
	case ID_FILE_RESTARTGAME:
		Game::GetGame()->RestartGame();
		break;
	case ID_FILE_EXITAPP:
		Game::GetGame()->QuitApp();
		break;
	case ID_GAME_CONTROLS:
		Game::GetGame()->GetWinMenu()->ActivatePopup(
			"Game Controls",
			"WASD - Move Player\nLeft Click / Hold - Attack\nScroll Wheel - Change Weapon\nLeft Shift - Dash\nP Key - Pause\n\nSee additional info in the INFORMATION menu page!"
		);
		break;
	case ID_HELP_ABOUTASTRALWAVEENGINE:
		Game::GetGame()->GetWinMenu()->ActivatePopup(
			"Astral Wave Engine",
			"Astral Wave Engine is an SDL2-based C++ 2D game engine.\n\nIt was created by Adam Leigh Williams in 2024.\n\nThis game, Ruins of Oblivion, was made as a final assessment."
		);
		break;
	case ID_CHEATS_MAXHEAL:
		// Check for playstate
		if (auto PS = dynamic_cast<PlayState*>(Game::GetGame()->GetGameStateMachine()->GetActiveGameState())) {
			// Check player is not nullptr
			if (PS->m_PlayerRef) {
				// Check player is already dead
				if (PS->m_PlayerRef->GetHealth() <= 0.0f) {
					Game::GetGame()->GetWinMenu()->ActivatePopupWarning(
						"Cheats",
						"Player is already dead!"
					);
					break;
				}
				
				// Max heal player
				PS->m_PlayerRef->ResetHealth();

				Game::GetGame()->GetWinMenu()->ActivatePopup(
					"Cheats",
					"Player healed to full!"
				);
				break;
			}
		}
		
		// Handle not in playstate
		Game::GetGame()->GetWinMenu()->ActivatePopupWarning(
			"Cheats",
			"No player to heal!"
		);
		break;
	case ID_CHEATS_OPENNEXTLEVEL:
		// Check for playstate
		if (auto PS = dynamic_cast<PlayState*>(Game::GetGame()->GetGameStateMachine()->GetActiveGameState())) {
			// Open next level
			PS->SetKeyCollected();

			Game::GetGame()->GetWinMenu()->ActivatePopup(
				"Cheats",
				"Next level opened!"
			);
			break;
		}

		// Handle not in playstate
		Game::GetGame()->GetWinMenu()->ActivatePopupWarning(
			"Cheats",
			"No level to open!"
		);
		break;
	case ID_CHEATS_MAXSCORE:
		// Check for playstate
		if (auto PS = dynamic_cast<PlayState*>(Game::GetGame()->GetGameStateMachine()->GetActiveGameState())) {
			// Open next level
			Game::GetGame()->m_Score = 999999;

			Game::GetGame()->GetWinMenu()->ActivatePopup(
				"Cheats",
				"Max score set!"
			);
			break;
		}

		// Handle not in playstate
		Game::GetGame()->GetWinMenu()->ActivatePopupWarning(
			"Cheats",
			"Must be in-game to set score!"
		);
		break;
	case ID_CHEATS_TOGGLEINVINCIBILITY:
		// Check for playstate
		if (auto PS = dynamic_cast<PlayState*>(Game::GetGame()->GetGameStateMachine()->GetActiveGameState())) {
			// Toggle invincibility
			PS->m_PlayerRef->ToggleInvincibility();

			Game::GetGame()->GetWinMenu()->ActivatePopup(
				"Cheats",
				"Player invincibility toggled!\n\nInvincibility only lasts for this level!"
			);
			break;
		}

		// Handle not in playstate
		Game::GetGame()->GetWinMenu()->ActivatePopupWarning(
			"Cheats",
			"No player to toggle invincibility!"
		);
		break;
	default:
		break;
	}
}

Vector2 Input::GetMousePos() const
{
	// Mouse position variables
	int x(0), y(0);

	// This function will change our x and y variables to the mouse location
	SDL_GetMouseState(&x, &y);
	
	return Vector2((float)x, (float)y);
}
