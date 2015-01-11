# Vanilla User Action

This plugin implements real in-game actions and jobs using *VanillaAction*, *VanillaCommand* and *VanillaJob* while relying on *VanillaSDL2* for input handling.

## Installation

Default path of plugin is `vanilla-user-action/vanilla-user-action`.

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillauseraction` (e.g. `#include <frts/vanillauseraction>`).

## Interfaces

### User Action Factory

This factory will register all commands, actions and jobs of this plugin.

Load using `frts/UserActionFactory` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::UserActionFactory`. It can also be found in the static class `UserActionIds`. 

## User Actions

Every user action configuration has an command id and an type id. The command id is for referencing this user action while the type id describes of what type the user action is. All type ids can also be found in the static class `UserActionIds`. Additionally every user action has a specific settings node described below.

    useraction:

        namespace: <string>
        
        useractions:
        
            - command: <string>
              type: <string representing an id>
              settings:
                <see below>

### Building

> Not yet implemented.

### Gathering

> Not yet implemented.

### Harvesting

User actions of this type will let the executing entity go to the specified position and destroy the object which should be harvested. Destroying this object will result in drops using the *Drop* component. Has type id `frts.vanillauseraction.useraction.harvest`.

    harvest_types: 
        - <string representing an id>
    requirements: 
        - <string representing an id>

### Production

> Not yet implemented.