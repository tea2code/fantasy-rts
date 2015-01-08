# Vanilla User Action

TOOD

## Installation

Default path of plugin is `vanilla-user-action/vanilla-user-action`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillauseraction` (e.g. `#include <frts/vanillauseraction>`).

## Interfaces

### User Action Factory

This factory will register all commands, actions and jobs of this plugin.

Load using `frts/UserActionFactory` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::UserActionFactory`. It can also be found in the static class `UserActionIds`. 