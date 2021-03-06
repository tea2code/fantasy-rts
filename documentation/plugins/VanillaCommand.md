# Vanilla Command

This plugin implements a variant of the [Command-Pattern](http://gameprogrammingpatterns.com/command.html). It makes a basic command interface available and allows to register custom commands into a factory. 

## Installation

Default path of plugin is `vanilla-command/vanilla-command`.

## Dependencies

No special dependency.

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillacommand` (e.g. `#include <frts/vanillacommand>`).

## Interfaces

### Command

A command represents an action which can be executed and in some cases also undone. Their default IDs can be found in the static class CommandIds.

### Command Config

Command plugin related configuration. 

Default ID can be found in the static class `CommandIds`.

Will identify itself by the name and type `frts::CommandConfig`. It can also be found in the static class `CommandIds`.

### Command Builder

Builder create commands and can be registered at the factory. They are identified by an ID and it is possible to create variants of commands by registering the same builder with different settings.

### Command Factory

The command factory is implemented as a utility module. It has a couple of preregistered commands but also allows to add custom commands from other plugins.

Load using `frts/CommandFactory` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::CommandFactory`. It can also be found in the static class `CommandIds`. 

## Configuration

The command config currently allows the configuration of undo related settings. 

    command:

        num_undo: <integer>
        
        undo_blacklist:
            - <string>

## Commands

Commands are registered during execution phase **Initialize Modules**. This means they are not accessible earlier. Trying so will result in an exception stating the command builder is not found with the given ID.

### QuitCommand

Quits the application. If `undo()` is during the current frame executed the command is reverted.  

Default ID can be found in the static class `CommandIds`.

### UndoCommand

Undoes the last executed command. 

Default ID can be found in the static class `CommandIds`.