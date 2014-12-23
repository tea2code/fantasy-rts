# Vanilla Event

This plugin implements a variant of the [Observer-Pattern](https://en.wikipedia.org/wiki/Observer_pattern). It allows to send and receive events outside the normal main loop. While this feature is helpful in a lot of cases it should never be used to completely avoid the main loop. Recommended use is receiving the event, storing it and handle it later in the `tick()` method. 

## Installation

Default path of plugin is `vanilla-event/vanilla-event`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillaevent` (e.g. `#include <frts/vanillaevent>`).

## Interfaces

### Event Manager

The event manager is implemented as a utility module. 

Load using `frts/EventManager` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::EventManager`. It can be also found in the static class `EventIds`. 