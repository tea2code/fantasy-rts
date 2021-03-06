#ifndef FRTS_KEY_H
#define FRTS_KEY_H

namespace frts
{
    /**
     * @brief Key representation.
     */
    enum class Key
    {
        // Numbers:
        Number0,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,

        // Letters:
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        // Function Keys:
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        // Arrows:
        Up,
        Down,
        Left,
        Right,

        // Special:
        Tab,
        Capslock,
        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,
        LeftAlt,
        RightAlt,
        Space,
        Enter,
        Backspace,
        Insert,
        Del,
        Home,
        End,
        PageUp,
        PageDown,
        Esc,
        Print,
        ScrollLock,
        Pause,

        // Keypad:
        KeyPad0,
        KeyPad1,
        KeyPad2,
        KeyPad3,
        KeyPad4,
        KeyPad5,
        KeyPad6,
        KeyPad7,
        KeyPad8,
        KeyPad9,
        KeyPadDivide,
        KeyPadMultiply,
        KeyPadMinus,
        KeyPadPlus,
        KeyPadEnter,
        KeyPadComma,
        Numlock,

        // Punctuation...:
        Comma,
        Semicolon,
        Dot,
        Colon,
        Underscore,
        Plus,
        Minus,
        Apostrophe,
        Hash,
        Multiply,
        Divide,
        Backslash,
        Question,
        LeftParenthesis,
        RightParenthesis,
        LeftBracket,
        RightBracket,
        LeftBrace,
        RightBrace,
        Ampersand,
        Percent,
        Dollar,
        DoubleQuote,
        Exclamation,
        At,
        Caret
    };
}

#endif // FRTS_KEY_H
