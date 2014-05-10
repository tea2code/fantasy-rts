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

### Blocking

Entities have the ability to block other entities. This is implemented by the blocking class. It allows different types of blocking and acts as an indication of what a entity can block and by what it is blocked.

### Entity

Entities represent all interactable objects in the world. 

#### Dynamic Entity

Dynamic entities are mostly living things which act on their own.

#### Resource

The resource entity represents are usable resource which can be dropped by other entities.

#### Static Entity

Static entities are most of the inanimated objects. They often drop resource entities.

#### Tile

Tiles represent the current floor. They usually don't allow any interaction.

### Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.