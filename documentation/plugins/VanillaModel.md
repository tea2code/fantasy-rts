# Vanilla Model

Represents the data model. Gives access to the region consisting of blocks in a 3D world. Defines entities and allows search for resources.

## Installation

Default path of plugin is `vanilla-model/vanilla-model`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillamodel` (e.g. `#include <frts/vanillamodel>`).

## Interface

### Model Factory

Utility module which acts as a factory to create model related objects like points, entities...

Include using `ModelFactory`.

## Blocking

Entities have the ability to block other entities. This is implemented by the blocking class. It allows different types of blocking and acts as an indication of what a entity can block and by what it is blocked.

## Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.