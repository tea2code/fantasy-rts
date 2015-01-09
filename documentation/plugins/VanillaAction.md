# Vanilla Action

This plugin helps executing user actions by providing a centralized manager. There can be only one active action at the time. The running action can be stopped or else will continue (each frame) until finished. 

For example started by a key command the user may select multiple trees for cutting them. After pressing the key the executed command will add a new action (stopping any running) which will then poll the mouse selection until finished. Then the action can add all the "Cut tree at position x" jobs to a job manager and end successful.

## Installation

Default path of plugin is `vanilla-action/vanilla-action`.

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillaaction` (e.g. `#include <frts/vanillaaction>`).

## Interfaces

### Action

The action interface must be implemented by any class which wants to use the action manager for its execution. All action methods are executed by the action manager or action handler and shouldn't be called manually. The method `stop()` is most likely called if another action wants to be executed because there can only be one at a time. The methods `execute()` and `stop()` are called every frame until they return `Finished` or `Cancel`. 

### Action Handler

The action handler is implemented as a tickable module. It will execute the currently running action every frame until finished.

Load using `frts/ActionHandler` in the `updateModules` section of the load file. 

Will identify itself by the name and type `frts::ActionHandler`. It can also be found in the static class `ActionIds`. 

### Action Manager

The action manager is implemented as a utility module. It will forward commands to the action handler.

Load using `frts/ActionManager` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::ActionManager`. It can also be found in the static class `ActionIds`. 

## Commands

This plugin implements also the following two commands using the *VanillaCommand* plugin.

### StopActionCommand

This command will stop the currently running action. The command id is `frts.vanillaaction.command.stopaction`.

### StopActionOrQuitCommand

This command will stop the currently running action. If no action is running it will quit the application. The command id is `frts.vanillaaction.command.stopactionorquit`.