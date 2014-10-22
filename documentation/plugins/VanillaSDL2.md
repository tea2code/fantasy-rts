# Vanilla SDL2

This plugin implements input handling and 2D visualization using [SDL2](http://www.libsdl.org/).

## Installation

Default path of plugin is `vanilla-sdl2/vanilla-sdl2`. Before including this plugin it is necessary to include the SDL2, SDL2_image and libpng libraries using following:

    vanilla-sdl2/SDL2
    vanilla-sdl2/SDL2_image
    vanilla-sdl2/zlib1
    vanilla-sdl2/libpng16-16

## Dependencies


The .pro file assumes that all dependencies are put into a directory *dependency* in the plugin root. For the naming of the individual directories of every dependency see the .pro file.

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillasdl2` (e.g. `#include <frts/vanillasdl2>`). If you only need input support use `frts/vanillasdl2input` (e.g. `#include <frts/vanillasdl2input>`).

For tests it is necessary to copy the SDL2_image library to the executable:

### Windows

    xcopy
    %{buildDir}\..\..\vanilla-sdl2\dependency\SDL2_image\i686-w64-mingw32\bin\SDL2_image.dll %{buildDir}  /eiy
    %{buildDir}

## Input/Event Handling

### Event Handler

The event handler module consumes all SDL2 events in the queue and handles them. These are mostly input events. 

Load using `frts/EventHandler` in the update (recommended) or render module section of the load file.

Will identify itself by the name `frts::EventHandler`.

### Input Handler

The input handler module allows to register commands to certain keys by using the configuration or the interface.  

Load using `frts/InputHandler` in the utility module section of the load file.

Will identify itself by the name `frts::InputHandler`.

### Configuration

    keys:
    
        - key: <string representing a key>
          command: <string representing a command id>

### Keys

Following keys are currently supported. If multiple names for one key exist they are space separated. Used in configuration files they are case insensitive. An equivalent enum exists and will be included using `frts/vanillasdl2input`.

#### Numbers:
        Number0 0
        Number1 1
        Number2 2
        Number3 3
        Number4 4
        Number5 5
        Number6 6
        Number7 7
        Number8 8
        Number9 9

#### Letters:
        A
        B
        C
        D
        E
        F
        G
        H
        I
        J
        K
        L
        M
        N
        O
        P
        Q
        R
        S
        T
        U
        V
        W
        X
        Y
        Z

#### Function Keys:
        F1
        F2
        F3
        F4
        F5
        F6
        F7
        F8
        F9
        F10
        F11
        F12

#### Arrows:
        Up
        Down
        Left
        Right

#### Special:
        Tab
        Capslock
        LeftShift
        RightShift
        LeftCtrl
        RightCtrl
        LeftAlt
        RightAlt
        Space
        Enter Return
        Backspace
        Insert
        Del Delete
        Home
        End
        PageUp
        PageDown
        Esc Escape
        Print
        ScrollLock
        Pause

#### Keypad:
        KeyPad0
        KeyPad1
        KeyPad2
        KeyPad3
        KeyPad4
        KeyPad5
        KeyPad6
        KeyPad7
        KeyPad8
        KeyPad9
        KeyPadDivide
        KeyPadMultiply
        KeyPadMinus
        KeyPadPlus
        KeyPadEnter KeyPadReturn
        KeyPadComma
        Numlock Clear

#### Punctuation...:
        Comma ,
        Semicolon ;
        Dot Period .
        Colon :
        Underscore _
        Plus +
        Minus Hyphen -
        Apostrophe Quote '
        Hash #
        Multiply Asterisk *
        Divide Slash /
        Backslash \
        Question ?
        LeftParenthesis (
        RightParenthesis )
        LeftBracket [
        RightBracket ]
        LeftBrace {
        RightBrace }
        Ampersand &
        Percent %
        Dollar $
        DoubleQuote
        Exclamation !
        At @
        Caret ^

## Graphic Output

### Drawer

Draws and updates the screen.

### Fps Manager

Limits the frame rate and calculates the current frame rate.

### Renderable

This component describes with which sprite a entity is rendered. If a sprite has the multiple attribute it also defines the index of the specific sub sprite.

Its config consists only of the sprite ID:

    sprite: <string representing an id>

### SDL2 Renderer

The renderer module manages everything graphic related. It allows to replace some parts like the fps manager and the drawer.

Load using `frts/SDL2Renderer` in the utility module section of the load file.

Will identify itself by the name `frts::SDL2Renderer`.

### Sprite Config

A complete sprite configuration consists of a list of sprite images with their pathes relative to the plugin root and a list of single sprites with image ID and position. A default `image` may be set below the `sprites` key. It will be used if no image is defined on a sprite. The same applies for default `height`and `width`. The position can be a single position or a list of positions. In the latter case it's possible to give a chance for each position. If no chance is given the probability for every position is the same. A `fallback` id of an sprite can be defined  below `sprites`.

    style:
        namespace: <string>
        
        images:
            namespace: <string>
            image:
                - name: <string>
                  path: <string>
    
        sprites:
            namespace: <string>
            
            fallback: <id>
            height: <int>
            image: <string>
            width: <int>
            
            sprite:
                - name: <string>
                  height: <int>
                  image: <string>
                  width: <int>
                  x: <int>
                  y: <int>
                  
                - name: <string>
                  height: <int>
                  width: <int>
                  multiple:
                     - x: <int>
                       y: <int>
                       chance: <float, optional>
                     - x: <int>
                       y: <int>
                       chance: <float, optional>