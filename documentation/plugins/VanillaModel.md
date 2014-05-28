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

### Block

A block describes a certain point in the world consisting of the entities at this point.

### Components

#### BlockedBy

Entities have the ability to block other entities. BlockedBy describes by what a entity is blocked.

#### Blocking

Entities have the ability to block other entities. Blocking describes what a entity blocks.

#### SortOrder

Entities may have a certain order in a block. The sort order component stores this attribute.

### Component Builder

Components are created using builders which can be registered at the model factory.

### Entity

Entities represent all interactable objects in the world. They consist of components representing their abilities, attributes...

### Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.

### Region

The region consists of blocks at certain positions and represents the game world. It allows to set the position of entities in the world and retrieve them or whole blocks. 

### Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completly empty but at the same moment a block is requested for the first time it will be created by the generator.