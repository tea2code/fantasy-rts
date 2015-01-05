# Fantasy-RTS

A fantasy real-time strategy game in the style of Dwarf Fortress. For now without a name. The main target is to create a game which provides the excellent fortress mode with a stable performance and full mod support. The prototype was developed using Python and Pygame (see directory "python-prototype"). It is now developed in C++. Beside the mod support as a core factor it will later support mobile platforms like Android and iOS.

## Roadmap

Current Version: **23**

- Version 1: Configuration.
- Version 2: Kernel.
- Version 3: Module interface.
- Version 4: Shared manager.
- Version 5: Plugins.
- Version 6: Refactoring, testing, documenting.
- Version 7: Core architecture with full plugin support.
- Version 8: Main loop, refactoring. Final kernel version.

Reached: *Spring 2014: Full plugin based architecture.*

- Version 9: Implementation of region, entity and resource data.
- Version 10: Configuration of model plugin.
- Version 11: Initial graphic support with SDL2. 
- Version 12: Design input support with SDL2.
- Version 13: Input support with SDL2.
- Version 14: Design graphic support with SDL2.
- Version 15: Graphic support with SDL2.
- Version 16: Maintenance & Demo Region Generator.
- Version 17: Keyboard control of map.
- Version 18: Controlable entities.
- Version 19: Perlin noise for hills, surface stuff and minerals.
- Version 20: Precalculated z-levels using parallel thread.
- Version 21: Event system.
- Version 22: Sidebar ui.
- Version 23: Action plugin.
- Version 24: Jobs plugin.
- Version 25: Digging.
- Version 26: Menu

Major goals:

- Spring 2015: Playable demo. Including basic economy, support for liquids, animals, digging, some enemies and a simple combat system.

## Ideas

- Sidebar with info about selected entity, commands and some kind of global info.
- Mobile Support (Android and iOS).
- Feelings plugin (every x + random seconds, update based on emotional attributes and handlers).
- Fluids.
- Fog of War / Unknown tiles should be blacked out.
- Multilanguage support.
- Better, realistic and more complex region generator.

## Documentation

A documentation of the ingame mechanisms and especially of the mod support is provided in the documentation directory. This also includes design sheets.
