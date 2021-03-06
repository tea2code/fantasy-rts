#include "KeyToSdl2Key.h"

#include <map>


SDL_Keycode frts::keyToSdl2Key(Key key)
{
    static std::map<Key, SDL_Keycode> mapping = {
        // Numbers:
        {Key::Number0, SDLK_0},
        {Key::Number1, SDLK_1},
        {Key::Number2, SDLK_2},
        {Key::Number3, SDLK_3},
        {Key::Number4, SDLK_4},
        {Key::Number5, SDLK_5},
        {Key::Number6, SDLK_6},
        {Key::Number7, SDLK_7},
        {Key::Number8, SDLK_8},
        {Key::Number9, SDLK_9},

        // Letters:
        {Key::A, SDLK_a},
        {Key::B, SDLK_b},
        {Key::C, SDLK_c},
        {Key::D, SDLK_d},
        {Key::E, SDLK_e},
        {Key::F, SDLK_f},
        {Key::G, SDLK_g},
        {Key::H, SDLK_h},
        {Key::I, SDLK_i},
        {Key::J, SDLK_j},
        {Key::K, SDLK_k},
        {Key::L, SDLK_l},
        {Key::M, SDLK_m},
        {Key::N, SDLK_n},
        {Key::O, SDLK_o},
        {Key::P, SDLK_p},
        {Key::Q, SDLK_q},
        {Key::R, SDLK_r},
        {Key::S, SDLK_s},
        {Key::T, SDLK_t},
        {Key::U, SDLK_u},
        {Key::V, SDLK_v},
        {Key::W, SDLK_w},
        {Key::X, SDLK_x},
        {Key::Y, SDLK_y},
        {Key::Z, SDLK_z},

        // Function Keys:
        {Key::F1, SDLK_F1},
        {Key::F2, SDLK_F2},
        {Key::F3, SDLK_F3},
        {Key::F4, SDLK_F4},
        {Key::F5, SDLK_F5},
        {Key::F6, SDLK_F6},
        {Key::F7, SDLK_F7},
        {Key::F8, SDLK_F8},
        {Key::F9, SDLK_F9},
        {Key::F10, SDLK_F10},
        {Key::F11, SDLK_F11},
        {Key::F12, SDLK_F12},

        // Arrows:
        {Key::Up, SDLK_UP},
        {Key::Down, SDLK_DOWN},
        {Key::Left, SDLK_LEFT},
        {Key::Right, SDLK_RIGHT},

        // Special:
        {Key::Tab, SDLK_TAB},
        {Key::Capslock, SDLK_CAPSLOCK},
        {Key::LeftShift, SDLK_LSHIFT},
        {Key::RightShift, SDLK_RSHIFT},
        {Key::LeftCtrl, SDLK_LCTRL},
        {Key::RightCtrl, SDLK_RCTRL},
        {Key::LeftAlt, SDLK_LALT},
        {Key::RightAlt, SDLK_RALT},
        {Key::Space, SDLK_SPACE},
        {Key::Enter, SDLK_RETURN},
        {Key::Backspace, SDLK_BACKSPACE},
        {Key::Insert, SDLK_INSERT},
        {Key::Del, SDLK_DELETE},
        {Key::Home, SDLK_HOME},
        {Key::End, SDLK_END},
        {Key::PageUp, SDLK_PAGEUP},
        {Key::PageDown, SDLK_PAGEDOWN},
        {Key::Esc, SDLK_ESCAPE},
        {Key::Print, SDLK_PRINTSCREEN},
        {Key::ScrollLock, SDLK_SCROLLLOCK},
        {Key::Pause, SDLK_PAUSE},

        // Keypad:
        {Key::KeyPad0, SDLK_KP_0},
        {Key::KeyPad1, SDLK_KP_1},
        {Key::KeyPad2, SDLK_KP_2},
        {Key::KeyPad3, SDLK_KP_3},
        {Key::KeyPad4, SDLK_KP_4},
        {Key::KeyPad5, SDLK_KP_5},
        {Key::KeyPad6, SDLK_KP_6},
        {Key::KeyPad7, SDLK_KP_7},
        {Key::KeyPad8, SDLK_KP_8},
        {Key::KeyPad9, SDLK_KP_9},
        {Key::KeyPadDivide, SDLK_KP_DIVIDE},
        {Key::KeyPadMultiply, SDLK_KP_MULTIPLY},
        {Key::KeyPadMinus, SDLK_KP_MINUS},
        {Key::KeyPadPlus, SDLK_KP_PLUS},
        {Key::KeyPadEnter, SDLK_KP_ENTER},
        {Key::KeyPadComma, SDLK_KP_COMMA},
        {Key::Numlock, SDLK_NUMLOCKCLEAR},

        // Punctuation...:
        {Key::Comma, SDLK_COMMA},
        {Key::Semicolon, SDLK_SEMICOLON},
        {Key::Dot, SDLK_PERIOD},
        {Key::Colon, SDLK_COLON},
        {Key::Underscore, SDLK_UNDERSCORE},
        {Key::Plus, SDLK_PLUS},
        {Key::Minus, SDLK_MINUS},
        {Key::Apostrophe, SDLK_QUOTE},
        {Key::Hash, SDLK_HASH},
        {Key::Multiply, SDLK_ASTERISK},
        {Key::Divide, SDLK_SLASH},
        {Key::Backslash, SDLK_BACKSLASH},
        {Key::Question, SDLK_QUESTION},
        {Key::LeftParenthesis, SDLK_LEFTPAREN},
        {Key::RightParenthesis, SDLK_RIGHTPAREN},
        {Key::LeftBracket, SDLK_LEFTBRACKET},
        {Key::RightBracket, SDLK_RIGHTBRACKET},
        {Key::LeftBrace, SDLK_KP_LEFTBRACE},
        {Key::RightBrace, SDLK_KP_RIGHTBRACE},
        {Key::Ampersand, SDLK_AMPERSAND},
        {Key::Percent, SDLK_PERCENT},
        {Key::Dollar, SDLK_DOLLAR},
        {Key::DoubleQuote, SDLK_QUOTEDBL},
        {Key::Exclamation, SDLK_EXCLAIM},
        {Key::At, SDLK_AT},
        {Key::Caret, SDLK_CARET},
    };
    return mapping.at(key);
}
