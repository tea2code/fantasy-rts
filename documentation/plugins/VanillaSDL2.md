# Vanilla SDL2

This plugin implements input handling and 2D visualization using [SDL2](http://www.libsdl.org/).

## Installation

Default path of plugin is `vanilla-sdl2/vanilla-sdl2`. Before including this plugin it is necessary to include the SDL2, SDL2_image, libpng, SDL2_ttf and libfreetype-6 libraries using following:

    vanilla-sdl2/SDL2
    vanilla-sdl2/SDL2_image
    vanilla-sdl2/SDL2_ttf
    vanilla-sdl2/zlib1
    vanilla-sdl2/libpng16-16
    vanilla-sdl2/libfreetype-6

## Dependencies

The .pro file assumes that all dependencies are put into a directory *dependency* in the plugin root. For the naming of the individual directories of every dependency see the .pro file.

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

Dependencies to other plugins are:

- VanillaCommand
- VanillaEvent
- VanillaModel

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillasdl2` (e.g. `#include <frts/vanillasdl2>`). If you only need input support use `frts/vanillasdl2input` (e.g. `#include <frts/vanillasdl2input>`).

For tests it is necessary to copy some libraries to the executable:

### Windows

    xcopy
    %{buildDir}\..\..\vanilla-sdl2\dependency\SDL2_image\i686-w64-mingw32\bin\SDL2_image.dll %{buildDir}  /eiy
    %{buildDir}
    
    xcopy
    %{buildDir}\..\..\vanilla-sdl2\dependency\SDL2_ttf\i686-w64-mingw32\bin\SDL2_ttf.dll %{buildDir}  /eiy
    %{buildDir}
    
    xcopy
    %{buildDir}\..\..\vanilla-sdl2\dependency\SDL2_ttf\i686-w64-mingw32\bin\libfreetype-6.dll %{buildDir}  /eiy
    %{buildDir}
    
    xcopy
    %{buildDir}\..\..\vanilla-sdl2\dependency\SDL2_ttf\i686-w64-mingw32\bin\zlib1.dll %{buildDir}  /eiy
    %{buildDir}

## Input/Event Handling

### SDL2 Event Handler

The event handler module consumes all SDL2 events in the queue and handles them. These are mostly input events. It also implements mouse and keyboard based selection (See **Events**). 

Load using `frts/SDL2EventHandler` in the `updateModules` (recommended) or `renderModules` section of the load file.

Will identify itself by the name and type `frts::SDL2EventHandler`. It can also be found in the static class `Sdl2Ids`

### Input Handler

The input handler module allows to register commands to certain keys by using the configuration or the interface.  

Load using `frts/InputHandler` in the `utilities` section of the load file.

Will identify itself by the name and type `frts::InputHandler`. It can also be found in the static class `Sdl2Ids`. 

### Configuration

Beside support for modifiers like ctrl or alt the input handler provides also a construct called "context". A key command without a context will always work. By providing a context the key will only work if the current context is the same. Switching the context is done by using `set_context` instead of `command`. Visually a context implements something like a menu and its submenus. 

Mouse buttons and modifies can also be combined.

    keys:
    
        default_context: <string representing an id>
    
        keys:
        
            - key: <string representing a key>
              alt: <boolean, optional, default false>
              ctrl: <boolean, optional, default false>
              shift: <boolean, optional, default false>
              context: <<string representing an id, optional>
              
              command: <string representing a command id, optional>
              set_context: <string representing an id, optional>

### Keys

Following keys are currently supported. If multiple names for one key exist they are space separated. Used in configuration files they are case insensitive. Equivalent enums exist for keyboard keys and mouse buttons and will be included using `frts/vanillasdl2input`. 

#### Mouse Buttons:

If no configuration for a mouse button is provided pressing it will result in a selection. The mouse buttons `X1` and `X2` are most likely the browser back and forward buttons.

        Mouse_Left
        Mouse_Middle
        Mouse_Right
        Mouse_X1
        Mouse_X2

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

### Selection Data

This data value contains data related to selecting positions using mouse or keyboard.

Default ID can be found in the static class `Sdl2Ids`.

Will identify itself by the name and type `frts::SelectionData`. It can also be found in the static class `Sdl2Ids`

## Commands

This plugin implements a couple of commands (using the *VanillaCommand* plugin) which are assigned to different keys. If necessary it adds these commands also to the undo blacklist. IDs can also be found in the static class `Sdl2Ids`.

### CloseContextCommand

This command allows to the current input context (See **Input/Event Handling**). Use command id `frts.vanillasdl2.command.closecontext`.

### MoveCursorCommand

This command allows movement of the cursor over the map. Following directions are implemented:

- **North:** Use command id `frts.vanillasdl2.command.movecursor.north`.
- **East:** Use command id `frts.vanillasdl2.command.movecursor.east`.
- **South:** Use command id `frts.vanillasdl2.command.movecursor.south`.
- **West:** Use command id `frts.vanillasdl2.command.movecursor.west`.
- **North East:** Use command id `frts.vanillasdl2.command.movecursor.northeast`.
- **South East:** Use command id `frts.vanillasdl2.command.movecursor.southeast`.
- **South West:** Use command id `frts.vanillasdl2.command.movecursor.southwest`.
- **North West:** Use command id `frts.vanillasdl2.command.movecursor.northwest`.

### MoveScreenCommand

This command allows movement of the visible screen over the map. Following directions are implemented:

- **North:** Use command id `frts.vanillasdl2.command.movescreen.north`.
- **East:** Use command id `frts.vanillasdl2.command.movescreen.east`.
- **South:** Use command id `frts.vanillasdl2.command.movescreen.south`.
- **West:** Use command id `frts.vanillasdl2.command.movescreen.west`.
- **Up:** Use command id `frts.vanillasdl2.command.movescreen.up`.
- **Down:** Use command id `frts.vanillasdl2.command.movescreen.down`.
- **North East:** Use command id `frts.vanillasdl2.command.movescreen.northeast`.
- **South East:** Use command id `frts.vanillasdl2.command.movescreen.southeast`.
- **South West:** Use command id `frts.vanillasdl2.command.movescreen.southwest`.
- **North West:** Use command id `frts.vanillasdl2.command.movescreen.northwest`.

Step width is configured in the `screen` configuration (see **Screen Config**).

### SelectCommand

This command allows to select a rectangular group of positions using the keyboard. Use command id `frts.vanillasdl2.command.select`.

### SwitchSidebarInfoIndexCommand

This command allows to switch the currently shown entity in the info area of the sidebar:

- **Next:** Use command id `frts.vanillasdl2.command.switchsidebarinfoindex.next`.
- **Previous:** Use command id `frts.vanillasdl2.command.switchsidebarinfoindex.previous`.

## Events

Using the *VanillaEvent* plugin this plugin will throw following events. IDs can also be found in the static class `Sdl2Ids`.

### Move Cursor Event

This event is thrown, when ever the cursor is moved by the user. It has the id `frts.vanillasdl2.event.movecursor`. It has a single point value with id `frts.vanillasdl2.event.movecursor.pos` describing the new position of the cursor.

### Selection Event

There are two variants of this event. The change event is raised when ever the current selection changes. It has the id `frts.vanillasdl2.event.selection.changed`. The finished event is raised when the selection is complete. It has the id `frts.vanillasdl2.event.selection.finished`. They have a point list value with id `frts.vanillasdl2.event.value.selection` describing the selection.

## Graphic Output

### Graphic Data

This data value contains common data related to graphic output. 

Default ID can be found in the static class `Sdl2Ids`.

Will identify itself by the name and type `frts::GraphicData`. It can also be found in the static class `Sdl2Ids`

### Renderable

This component describes with which sprite a entity is rendered. If a sprite has the multiple attribute it also defines the index of the specific sub sprite.

Default ID can be found in the static class `Sdl2Ids`.

Its config consists of the sprite ID and a optional transparency value:

    sprite: <string representing an id>
    stacking: <boolean, optional, default true>
    transparency: <integer greater or equal 0, optional>

If `stacking` is set to `false` this will prevent multiple drawings of the same renderable type over each other. The same renderable is defined as having the same sprite id.

If `transparency` is given the defined number of blocks below the current one are rendered. This is currently only for the background (the lowest) entity supported. It only works if the sprites have a alpha channel with at least some transparency.

### SDL2 Renderer

The renderer module manages everything graphic related. 

Load using `frts/SDL2Renderer` in the `renderModules` section of the load file.

Will identify itself by the name and type `frts::SDL2Renderer`. It can also be found in the static class `Sdl2Ids`

#### Screen Config

The screen config defines the cursor entity, selection entity, the size of the visible screen (and thus defines the windows size), the screen movement size, the number of frame rate measures used to calculate the average frame rate, the window title (use `%1%` as an placeholder for the frame rate and `%2%` as a placeholder for the zoom) and the size of a single tile. The screen size and screen movement size should be multiples of the tile size or else they will be cropped accordingly.

    screen:
    
        cursor: <string representing an id>
        
        selection: <string representing an id>

        num_fps_avg: <integer greater 0>
    
        height: <integer greater 0>
        width: <integer greater 0>
        
        screen_move_x: <integer greater 0>
        screen_move_y: <integer greater 0>
        
        sidebar_width: <integer greater 0>
        
        title: <string>

        start_zoom: <float>

        zoom_levels:
            - <float>
            
    tile:
    
        height: <integer greater 0>
        width: <integer greater 0>

#### Style Config

A complete style configuration consists of a list of sprite images with their pathes relative to the plugin root and a list of single sprites with image ID and position. A default `image` may be set below the `sprites` key. It will be used if no image is defined on a sprite. The same applies for default `height`and `width`. The position can be a single position or a list of positions. In the latter case it's possible to give a chance for each position. If no chance is given the probability for every position is the same. A `fallback` id of an sprite must be defined  below `sprites`.

It is possible to define a background color on the `style` node. This is used for background aka. behind the sprites filling of the screen. By default black is used.

    style:
        namespace: <string>
        
        background:
            r: <integer between 0 and 255, optional>
            g: <integer between 0 and 255, optional>
            b: <integer between 0 and 255, optional>
        
        images:
            namespace: <string>
            image:
                - name: <string>
                  path: <string>
    
        sprites:
            namespace: <string>
            
            fallback: <id>
            height: <integer greater 0>
            image: <string>
            width: <integer greater 0>
            
            sprite:
                - name: <string>
                  height: <integer greater 0>
                  image: <string>
                  width: <integer greater 0>
                  x: <integer greater 0>
                  y: <integer greater 0>
                  
                - name: <string>
                  height: <integer greater 0>
                  width: <integer greater 0>
                  multiple:
                     - x: <integer greater 0>
                       y: <integer greater 0>
                       chance: <float, optional>
                     - x: <integer greater 0>
                       y: <integer greater 0>
                       chance: <float, optional>
                       
#### Sidebar Config

Beside the style configuration for the map there is another one for the sidebar. The key `values` of `events` is optional.

    sidebar:
    
        background:
            r: <integer between 0 and 255, optional>
            g: <integer between 0 and 255, optional>
            b: <integer between 0 and 255, optional>
         
        events-height: <integer greater 0>
        
        events-update: <integer greater/equal 0>
         
        font-color:
            r: <integer between 0 and 255, optional>
            g: <integer between 0 and 255, optional>
            b: <integer between 0 and 255, optional>
            
        font-path: <string>
        
        font-size: <integer greater 0>
            
        info-only-with-component: <boolean>

        info-text: <string>

        info-text-height: <integer greater 0>
            
        info-update: <integer greater/equal 0>
            
        line-color:
            r: <integer between 0 and 255, optional>
            g: <integer between 0 and 255, optional>
            b: <integer between 0 and 255, optional>
         
        padding: <integer greater/equal 0>

        tile-background:
            r: <integer between 0 and 255, optional>
            g: <integer between 0 and 255, optional>
            b: <integer between 0 and 255, optional>
            
        tile-zoom: <integer greater 0>
            
        events:
            - type: <string representing an id>
              text: <string>
              values:
                - <string representing an id>