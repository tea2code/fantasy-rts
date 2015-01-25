# Vanilla User Action

This plugin implements real in-game actions and jobs using *VanillaAction*, *VanillaCommand* and *VanillaJob* while relying on *VanillaSDL2* for input handling.

## Installation

Default path of plugin is `vanilla-user-action/vanilla-user-action`.

## Dependencies

- VanillaAction
- VanillaCommand
- VanillaEvent
- VanillaJob
- VanillaModel
- VanillaSDL2

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillauseraction` (e.g. `#include <frts/vanillauseraction>`).

## Interfaces

### User Action Factory

This factory will register all commands, actions and jobs of this plugin. It also provides different helper methods which are useful for creating actions and jobs.

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

### Carving

User actions of this type allow to create buildings and other objects from harvestable objects. Basically converting them. This user action supports placing teleports for example for carving stairs from rock. Dropping can be enabled but is not by default. Has type id `frts.vanillauseraction.useraction.carve`.

The teleport node is optional in the settings. If it is available a teleport will be created between the job position and the relative position described by this node.

    carve_types: 
         - <string representing an id>
    drop: <boolean, optional, default false>
    harvest_types: 
        - <string representing an id>
    jobmarker: <string representing an id>
    requirements: 
        - <string representing an id>
    teleport:
        x: <integer>
        y: <integer>
        z: <integer>

### Gathering

> Not yet implemented.

### Harvesting

User actions of this type will let the executing entity go to the specified position and destroy the object which should be harvested. Destroying this object will result in drops using the *Drop* component. Has type id `frts.vanillauseraction.useraction.harvest`.

    harvest_types: 
        - <string representing an id>
    jobmarker: <string representing an id>
    requirements: 
        - <string representing an id>

### Production

> Not yet implemented.

### Special

#### Stop Jobs

General user action to stop all or specific jobs within the selection. Jobs are found by their job markers. Has type id `frts.vanillauseraction.useraction.stop`. There are three different variants depending on the configuration. If the `settings` node is empty all found jobs are stopped. If a list of job ids is given jobs with these ids will be stopped. If a list of job types is given these types will be stopped. The last two can be combined.

    jobs:
        - <string representing an id>
    types:
        - <string representing an id>