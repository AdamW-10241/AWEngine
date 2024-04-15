#pragma once
#include "SDL2/SDL_events.h"

typedef enum
{
    AW_KEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
     /* @{ */

    AW_KEY_A = 4,
    AW_KEY_B = 5,
    AW_KEY_C = 6,
    AW_KEY_D = 7,
    AW_KEY_E = 8,
    AW_KEY_F = 9,
    AW_KEY_G = 10,
    AW_KEY_H = 11,
    AW_KEY_I = 12,
    AW_KEY_J = 13,
    AW_KEY_K = 14,
    AW_KEY_L = 15,
    AW_KEY_M = 16,
    AW_KEY_N = 17,
    AW_KEY_O = 18,
    AW_KEY_P = 19,
    AW_KEY_Q = 20,
    AW_KEY_R = 21,
    AW_KEY_S = 22,
    AW_KEY_T = 23,
    AW_KEY_U = 24,
    AW_KEY_V = 25,
    AW_KEY_W = 26,
    AW_KEY_X = 27,
    AW_KEY_Y = 28,
    AW_KEY_Z = 29,

    AW_KEY_1 = 30,
    AW_KEY_2 = 31,
    AW_KEY_3 = 32,
    AW_KEY_4 = 33,
    AW_KEY_5 = 34,
    AW_KEY_6 = 35,
    AW_KEY_7 = 36,
    AW_KEY_8 = 37,
    AW_KEY_9 = 38,
    AW_KEY_0 = 39,

    AW_KEY_RETURN = 40,
    AW_KEY_ESCAPE = 41,
    AW_KEY_BACKSPACE = 42,
    AW_KEY_TAB = 43,
    AW_KEY_SPACE = 44,

    AW_KEY_MINUS = 45,
    AW_KEY_EQUALS = 46,
    AW_KEY_LEFTBRACKET = 47,
    AW_KEY_RIGHTBRACKET = 48,
    AW_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    AW_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate AW_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    AW_KEY_SEMICOLON = 51,
    AW_KEY_APOSTROPHE = 52,
    AW_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    AW_KEY_COMMA = 54,
    AW_KEY_PERIOD = 55,
    AW_KEY_SLASH = 56,

    AW_KEY_CAPSLOCK = 57,

    AW_KEY_F1 = 58,
    AW_KEY_F2 = 59,
    AW_KEY_F3 = 60,
    AW_KEY_F4 = 61,
    AW_KEY_F5 = 62,
    AW_KEY_F6 = 63,
    AW_KEY_F7 = 64,
    AW_KEY_F8 = 65,
    AW_KEY_F9 = 66,
    AW_KEY_F10 = 67,
    AW_KEY_F11 = 68,
    AW_KEY_F12 = 69,

    AW_KEY_PRINTSCREEN = 70,
    AW_KEY_SCROLLLOCK = 71,
    AW_KEY_PAUSE = 72,
    AW_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    AW_KEY_HOME = 74,
    AW_KEY_PAGEUP = 75,
    AW_KEY_DELETE = 76,
    AW_KEY_END = 77,
    AW_KEY_PAGEDOWN = 78,
    AW_KEY_RIGHT = 79,
    AW_KEY_LEFT = 80,
    AW_KEY_DOWN = 81,
    AW_KEY_UP = 82,

    AW_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    AW_KEY_KP_DIVIDE = 84,
    AW_KEY_KP_MULTIPLY = 85,
    AW_KEY_KP_MINUS = 86,
    AW_KEY_KP_PLUS = 87,
    AW_KEY_KP_ENTER = 88,
    AW_KEY_KP_1 = 89,
    AW_KEY_KP_2 = 90,
    AW_KEY_KP_3 = 91,
    AW_KEY_KP_4 = 92,
    AW_KEY_KP_5 = 93,
    AW_KEY_KP_6 = 94,
    AW_KEY_KP_7 = 95,
    AW_KEY_KP_8 = 96,
    AW_KEY_KP_9 = 97,
    AW_KEY_KP_0 = 98,
    AW_KEY_KP_PERIOD = 99,

    AW_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    AW_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
    AW_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    AW_KEY_KP_EQUALS = 103,
    AW_KEY_F13 = 104,
    AW_KEY_F14 = 105,
    AW_KEY_F15 = 106,
    AW_KEY_F16 = 107,
    AW_KEY_F17 = 108,
    AW_KEY_F18 = 109,
    AW_KEY_F19 = 110,
    AW_KEY_F20 = 111,
    AW_KEY_F21 = 112,
    AW_KEY_F22 = 113,
    AW_KEY_F23 = 114,
    AW_KEY_F24 = 115,
    AW_KEY_EXECUTE = 116,
    AW_KEY_HELP = 117,    /**< AL Integrated Help Center */
    AW_KEY_MENU = 118,    /**< Menu (show menu) */
    AW_KEY_SELECT = 119,
    AW_KEY_STOP = 120,    /**< AC Stop */
    AW_KEY_AGAIN = 121,   /**< AC Redo/Repeat */
    AW_KEY_UNDO = 122,    /**< AC Undo */
    AW_KEY_CUT = 123,     /**< AC Cut */
    AW_KEY_COPY = 124,    /**< AC Copy */
    AW_KEY_PASTE = 125,   /**< AC Paste */
    AW_KEY_FIND = 126,    /**< AC Find */
    AW_KEY_MUTE = 127,
    AW_KEY_VOLUMEUP = 128,
    AW_KEY_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     AW_KEY_LOCKINGCAPSLOCK = 130,  */
    /*     AW_KEY_LOCKINGNUMLOCK = 131, */
    /*     AW_KEY_LOCKINGSCROLLLOCK = 132, */
    AW_KEY_KP_COMMA = 133,
    AW_KEY_KP_EQUALSAS400 = 134,

    AW_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    AW_KEY_INTERNATIONAL2 = 136,
    AW_KEY_INTERNATIONAL3 = 137, /**< Yen */
    AW_KEY_INTERNATIONAL4 = 138,
    AW_KEY_INTERNATIONAL5 = 139,
    AW_KEY_INTERNATIONAL6 = 140,
    AW_KEY_INTERNATIONAL7 = 141,
    AW_KEY_INTERNATIONAL8 = 142,
    AW_KEY_INTERNATIONAL9 = 143,
    AW_KEY_LANG1 = 144, /**< Hangul/English toggle */
    AW_KEY_LANG2 = 145, /**< Hanja conversion */
    AW_KEY_LANG3 = 146, /**< Katakana */
    AW_KEY_LANG4 = 147, /**< Hiragana */
    AW_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    AW_KEY_LANG6 = 149, /**< reserved */
    AW_KEY_LANG7 = 150, /**< reserved */
    AW_KEY_LANG8 = 151, /**< reserved */
    AW_KEY_LANG9 = 152, /**< reserved */

    AW_KEY_ALTERASE = 153,    /**< Erase-Eaze */
    AW_KEY_SYSREQ = 154,
    AW_KEY_CANCEL = 155,      /**< AC Cancel */
    AW_KEY_CLEAR = 156,
    AW_KEY_PRIOR = 157,
    AW_KEY_RETURN2 = 158,
    AW_KEY_SEPARATOR = 159,
    AW_KEY_OUT = 160,
    AW_KEY_OPER = 161,
    AW_KEY_CLEARAGAIN = 162,
    AW_KEY_CRSEL = 163,
    AW_KEY_EXSEL = 164,

    AW_KEY_KP_00 = 176,
    AW_KEY_KP_000 = 177,
    AW_KEY_THOUSANDSSEPARATOR = 178,
    AW_KEY_DECIMALSEPARATOR = 179,
    AW_KEY_CURRENCYUNIT = 180,
    AW_KEY_CURRENCYSUBUNIT = 181,
    AW_KEY_KP_LEFTPAREN = 182,
    AW_KEY_KP_RIGHTPAREN = 183,
    AW_KEY_KP_LEFTBRACE = 184,
    AW_KEY_KP_RIGHTBRACE = 185,
    AW_KEY_KP_TAB = 186,
    AW_KEY_KP_BACKSPACE = 187,
    AW_KEY_KP_A = 188,
    AW_KEY_KP_B = 189,
    AW_KEY_KP_C = 190,
    AW_KEY_KP_D = 191,
    AW_KEY_KP_E = 192,
    AW_KEY_KP_F = 193,
    AW_KEY_KP_XOR = 194,
    AW_KEY_KP_POWER = 195,
    AW_KEY_KP_PERCENT = 196,
    AW_KEY_KP_LESS = 197,
    AW_KEY_KP_GREATER = 198,
    AW_KEY_KP_AMPERSAND = 199,
    AW_KEY_KP_DBLAMPERSAND = 200,
    AW_KEY_KP_VERTICALBAR = 201,
    AW_KEY_KP_DBLVERTICALBAR = 202,
    AW_KEY_KP_COLON = 203,
    AW_KEY_KP_HASH = 204,
    AW_KEY_KP_SPACE = 205,
    AW_KEY_KP_AT = 206,
    AW_KEY_KP_EXCLAM = 207,
    AW_KEY_KP_MEMSTORE = 208,
    AW_KEY_KP_MEMRECALL = 209,
    AW_KEY_KP_MEMCLEAR = 210,
    AW_KEY_KP_MEMADD = 211,
    AW_KEY_KP_MEMSUBTRACT = 212,
    AW_KEY_KP_MEMMULTIPLY = 213,
    AW_KEY_KP_MEMDIVIDE = 214,
    AW_KEY_KP_PLUSMINUS = 215,
    AW_KEY_KP_CLEAR = 216,
    AW_KEY_KP_CLEARENTRY = 217,
    AW_KEY_KP_BINARY = 218,
    AW_KEY_KP_OCTAL = 219,
    AW_KEY_KP_DECIMAL = 220,
    AW_KEY_KP_HEXADECIMAL = 221,

    AW_KEY_LCTRL = 224,
    AW_KEY_LSHIFT = 225,
    AW_KEY_LALT = 226, /**< alt, option */
    AW_KEY_LGUI = 227, /**< windows, command (apple), meta */
    AW_KEY_RCTRL = 228,
    AW_KEY_RSHIFT = 229,
    AW_KEY_RALT = 230, /**< alt gr, option */
    AW_KEY_RGUI = 231, /**< windows, command (apple), meta */

    AW_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

                                 /* @} *//* Usage page 0x07 */

                                 /**
                                  *  \name Usage page 0x0C
                                  *
                                  *  These values are mapped from usage page 0x0C (USB consumer page).
                                  *  See https://usb.org/sites/default/files/hut1_2.pdf
                                  *
                                  *  There are way more keys in the spec than we can represent in the
                                  *  current scancode range, so pick the ones that commonly come up in
                                  *  real world usage.
                                  */
                                  /* @{ */

    AW_KEY_AUDIONEXT = 258,
    AW_KEY_AUDIOPREV = 259,
    AW_KEY_AUDIOSTOP = 260,
    AW_KEY_AUDIOPLAY = 261,
    AW_KEY_AUDIOMUTE = 262,
    AW_KEY_MEDIASELECT = 263,
    AW_KEY_WWW = 264,             /**< AL Internet Browser */
    AW_KEY_MAIL = 265,
    AW_KEY_CALCULATOR = 266,      /**< AL Calculator */
    AW_KEY_COMPUTER = 267,
    AW_KEY_AC_SEARCH = 268,       /**< AC Search */
    AW_KEY_AC_HOME = 269,         /**< AC Home */
    AW_KEY_AC_BACK = 270,         /**< AC Back */
    AW_KEY_AC_FORWARD = 271,      /**< AC Forward */
    AW_KEY_AC_STOP = 272,         /**< AC Stop */
    AW_KEY_AC_REFRESH = 273,      /**< AC Refresh */
    AW_KEY_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
     /* @{ */

    AW_KEY_BRIGHTNESSDOWN = 275,
    AW_KEY_BRIGHTNESSUP = 276,
    AW_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    AW_KEY_KBDILLUMTOGGLE = 278,
    AW_KEY_KBDILLUMDOWN = 279,
    AW_KEY_KBDILLUMUP = 280,
    AW_KEY_EJECT = 281,
    AW_KEY_SLEEP = 282,           /**< SC System Sleep */

    AW_KEY_APP1 = 283,
    AW_KEY_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
     /* @{ */

    AW_KEY_AUDIOREWIND = 285,
    AW_KEY_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
     /* @{ */

    AW_KEY_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    AW_KEY_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    AW_KEY_CALL = 289, /**< Used for accepting phone calls. */
    AW_KEY_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    AW_NUM_KEY = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} AW_Key;

enum AW_MouseButton : unsigned int {
    AW_MOUSE_LEFT = 0,
    AW_MOUSE_MIDDLE,
    AW_MOUSE_RIGHT,

    AW_NUM_BUTTONS  // Not a key just marks number of buttons
};

struct Vector2;

class Input {
public:
	Input() = default;
	~Input() = default;

	// Process inputs being pressed by the player
	void ProcessInput();
	// Test if the key is pressed down
	bool IsKeyDown(AW_Key Key);
    // Test if a mouse button is down
    bool IsMouseButtonDown(AW_MouseButton Button);
    // Get the position of the mouse on the window
    Vector2 GetMousePos() const;

private:
    // Detect the state of the mouse
    void DetectMouseButtonState(unsigned int Event, bool Value);

    // Listen and react to windows menu events
    void HandleWinMenuEvents(SDL_Event* Event);

private:
    // State of each button on the mouse
    bool m_MouseState[3] = { false };

};