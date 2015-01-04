# Vanilla Action

This plugin helps executing user actions by providing a centralized manager. There can be only one active action at the time. The running action can be stopped or else will continue (each frame) until finished. 

For example started by a key command the user may select multiple trees for cutting them. After pressing the key the executed command will add a new action (stopping any running) which will then poll the mouse selection until finished. Then the action can add all the "Cut tree at position x" jobs to a job manager and end successful.

## Installation

Default path of plugin is `vanilla-action/vanilla-action`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillaaction` (e.g. `#include <frts/vanillaaction>`).

## Interfaces

### Action

### Action Manager

## Commands

This plugin implements also the following two commands using the *VanillaCommand* plugin.

### StopActionCommand

### StopActionOrQuitCommand