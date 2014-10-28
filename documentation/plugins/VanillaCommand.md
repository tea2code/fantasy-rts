# Vanilla Command

This plugin implements a variant of the [Command-Pattern](http://gameprogrammingpatterns.com/command.html). It makes a basic command interface available and allows to register custom commands into a factory. 

## Installation

Default path of plugin is `vanilla-command/vanilla-command`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillacommand` (e.g. `#include <frts/vanillacommand>`).

## Interfaces

### Command

A command represents an action which can be executed and in some cases also undone. Their default IDs can be found in the static class CommandIds.

### CommandBuilder

Builder create commands and can be registered at the factory. They are identified by an ID and it is possible to create variants of commands by registering the same builder with different settings.

### CommandFactory

The command factory is implemented as a utility module. It has a couple of pre registered commands but also allows to add custom commands from other plugins.

Load using `frts/CommandFactory` in the `utilities` section of the load file. This is also the utility ID. It can be found in the static class `CommandIds`. 

Will identify itself by the name `frts::CommandFactory`.

## Commands

Commands are registered during execution phase 10 (module initialization). This means they are not accessible earlier. Trying so will result in an exception stating the command builder is not found with the given ID.

### QuitCommand

Quits the application. If `undo()` is during the current frame executed the command is reverted.  

Default ID can be found in the static class `CommandIds`.