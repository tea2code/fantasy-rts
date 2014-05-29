# Vanilla Model

Represents the data model. Gives access to the region consisting of blocks in a 3D world. Defines entities and allows search for resources.

## Installation

Default path of plugin is `vanilla-model/vanilla-model`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillamodel` (e.g. `#include <frts/vanillamodel>`).

An additional include `frts/vanillamodeldev` exists if you need to develope your own components... It contains the normal include and some additional headers like for component builder or the region interface.

## Interfaces

### Model Factory

Utility module which acts as a factory to create model related objects like points, entities...

Load using `ModelFactory` in the utilities section of the load file.

### Block

A block describes a certain point in the world consisting of the entities at this point.

### Components

Components describe the attributes, abilities... of a entity.

#### BlockedBy

Entities have the ability to block other entities. BlockedBy describes by what a entity is blocked.

Default ID is `frts.vanillamodel.entity.component.blockedby`.

#### Blocking

Entities have the ability to block other entities. Blocking describes what a entity blocks.

Default ID is `frts.vanillamodel.entity.component.blocking`.

#### HasResource

Entities may contain resources which can be harvested. The type of this component is also the resource type.

Default ID is `frts.vanillamodel.entity.component.hasresource.<resource-name>`.    
For example: `frts.vanillamodel.entity.component.hasresource.wood`

#### IsResource

Entities with this component represent a resource. The type of this component is also the resource type.

Default ID is `frts.vanillamodel.entity.component.isresource.<resource-name>`.    
For example: `frts.vanillamodel.entity.component.isresource.wood`

#### SortOrder

Entities may have a certain order in a block. The sort order component stores this attribute.

Default ID is `frts.vanillamodel.entity.component.sortorder`.

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