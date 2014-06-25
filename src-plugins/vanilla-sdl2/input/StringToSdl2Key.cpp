#include "StringToSdl2Key.h"

#include <algorithm>
#include <unordered_map>


SDL_Keycode frts::stringToSdl2Key(std::string keyString)
{
    static std::unordered_map<std::string, SDL_Keycode> mapping = {
        // Numbers:
        {"number0", SDLK_0},
        {"0", SDLK_0},
        {"number1", SDLK_1},
        {"1", SDLK_1},
        {"number2", SDLK_2},
        {"2", SDLK_2},
        {"number3", SDLK_3},
        {"3", SDLK_3},
        {"number4", SDLK_4},
        {"4", SDLK_4},
        {"number5", SDLK_5},
        {"5", SDLK_5},
        {"number6", SDLK_6},
        {"6", SDLK_6},
        {"number7", SDLK_7},
        {"7", SDLK_7},
        {"number8", SDLK_8},
        {"8", SDLK_8},
        {"number9", SDLK_9},
        {"9", SDLK_9},

        // Letters:
        {"a", SDLK_a},
        {"b", SDLK_b},
        {"c", SDLK_c},
        {"d", SDLK_d},
        {"e", SDLK_e},
        {"f", SDLK_f},
        {"g", SDLK_g},
        {"h", SDLK_h},
        {"i", SDLK_i},
        {"j", SDLK_j},
        {"k", SDLK_k},
        {"l", SDLK_l},
        {"m", SDLK_m},
        {"n", SDLK_n},
        {"o", SDLK_o},
        {"p", SDLK_p},
        {"q", SDLK_q},
        {"r", SDLK_r},
        {"s", SDLK_s},
        {"t", SDLK_t},
        {"u", SDLK_u},
        {"v", SDLK_v},
        {"w", SDLK_w},
        {"x", SDLK_x},
        {"y", SDLK_y},
        {"z", SDLK_z},

        // Function Keys:
        {"f1", SDLK_F1},
        {"f2", SDLK_F2},
        {"f3", SDLK_F3},
        {"f4", SDLK_F4},
        {"f5", SDLK_F5},
        {"f6", SDLK_F6},
        {"f7", SDLK_F7},
        {"f8", SDLK_F8},
        {"f9", SDLK_F9},
        {"f10", SDLK_F10},
        {"f11", SDLK_F11},
        {"f12", SDLK_F12},

        // Arrows:
        {"up", SDLK_UP},
        {"down", SDLK_DOWN},
        {"left", SDLK_LEFT},
        {"right", SDLK_RIGHT},

        // Special:
        {"tab", SDLK_TAB},
        {"capslock", SDLK_CAPSLOCK},
        {"leftshift", SDLK_LSHIFT},
        {"rightshift", SDLK_RSHIFT},
        {"leftctrl", SDLK_LCTRL},
        {"rightctrl", SDLK_RCTRL},
        {"leftalt", SDLK_LALT},
        {"rightalt", SDLK_RALT},
        {"space", SDLK_SPACE},
        {"enter", SDLK_RETURN},
        {"return", SDLK_RETURN},
        {"backspace", SDLK_BACKSPACE},
        {"insert", SDLK_INSERT},
        {"del", SDLK_DELETE},
        {"delete", SDLK_DELETE},
        {"home", SDLK_HOME},
        {"end", SDLK_END},
        {"pageup", SDLK_PAGEUP},
        {"pagedown", SDLK_PAGEDOWN},
        {"esc", SDLK_ESCAPE},
        {"escape", SDLK_ESCAPE},
        {"print", SDLK_PRINTSCREEN},
        {"scrolllock", SDLK_SCROLLLOCK},
        {"pause", SDLK_PAUSE},

        // Keypad:
        {"keypad0", SDLK_KP_0},
        {"keypad1", SDLK_KP_1},
        {"keypad2", SDLK_KP_2},
        {"keypad3", SDLK_KP_3},
        {"keypad4", SDLK_KP_4},
        {"keypad5", SDLK_KP_5},
        {"keypad6", SDLK_KP_6},
        {"keypad7", SDLK_KP_7},
        {"keypad8", SDLK_KP_8},
        {"keypad9", SDLK_KP_9},
        {"keypaddivide", SDLK_KP_DIVIDE},
        {"keypadmultiply", SDLK_KP_MULTIPLY},
        {"keypadminus", SDLK_KP_MINUS},
        {"keypadplus", SDLK_KP_PLUS},
        {"keypadenter", SDLK_KP_ENTER},
        {"keypadreturn", SDLK_KP_ENTER},
        {"keypadcomma", SDLK_KP_COMMA},
        {"numlock", SDLK_NUMLOCKCLEAR},
        {"clear", SDLK_NUMLOCKCLEAR},

        // Punctuation...:
        {"comma", SDLK_COMMA},
        {",", SDLK_COMMA},
        {"semicolon", SDLK_SEMICOLON},
        {";", SDLK_SEMICOLON},
        {"dot", SDLK_PERIOD},
        {"period", SDLK_PERIOD},
        {".", SDLK_PERIOD},
        {"colon", SDLK_COLON},
        {":", SDLK_COLON},
        {"underscore", SDLK_UNDERSCORE},
        {"_", SDLK_UNDERSCORE},
        {"plus", SDLK_PLUS},
        {"+", SDLK_PLUS},
        {"minus", SDLK_MINUS},
        {"hyphen", SDLK_MINUS},
        {"-", SDLK_MINUS},
        {"apostrophe", SDLK_QUOTE},
        {"quote", SDLK_QUOTE},
        {"hash", SDLK_HASH},
        {"#", SDLK_HASH},
        {"multiply", SDLK_ASTERISK},
        {"asterisk", SDLK_ASTERISK},
        {"*", SDLK_ASTERISK},
        {"divide", SDLK_SLASH},
        {"slash", SDLK_SLASH},
        {"/", SDLK_SLASH},
        {"backslash", SDLK_BACKSLASH},
        {"\\", SDLK_BACKSLASH},
        {"question", SDLK_QUESTION},
        {"?", SDLK_QUESTION},
        {"leftparenthesis", SDLK_LEFTPAREN},
        {"(", SDLK_LEFTPAREN},
        {"rightparenthesis", SDLK_RIGHTPAREN},
        {")", SDLK_RIGHTPAREN},
        {"leftbracket", SDLK_LEFTBRACKET},
        {"[", SDLK_LEFTBRACKET},
        {"rightbracket", SDLK_RIGHTBRACKET},
        {"]", SDLK_RIGHTBRACKET},
        {"leftbrace", SDLK_KP_LEFTBRACE},
        {"{", SDLK_KP_LEFTBRACE},
        {"rightbrace", SDLK_KP_RIGHTBRACE},
        {"}", SDLK_KP_RIGHTBRACE},
        {"ampersand", SDLK_AMPERSAND},
        {"&", SDLK_AMPERSAND},
        {"percent", SDLK_PERCENT},
        {"%", SDLK_PERCENT},
        {"dollar", SDLK_DOLLAR},
        {"$", SDLK_DOLLAR},
        {"doublequote", SDLK_QUOTEDBL},
        {"exclamation", SDLK_EXCLAIM},
        {"!", SDLK_EXCLAIM},
        {"at", SDLK_AT},
        {"@", SDLK_AT},
        {"caret", SDLK_CARET},
        {"^", SDLK_CARET}
    };
    std::transform(keyString.begin(), keyString.end(), keyString.begin(), ::tolower);
    return mapping.at(keyString);
}
