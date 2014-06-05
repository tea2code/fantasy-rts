# Vanilla Model

Represents the data model. Gives access to the region consisting of blocks in a 3D world. Defines entities and allows search for resources.

## Installation

Default path of plugin is `vanilla-model/vanilla-model`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillamodel` (e.g. `#include <frts/vanillamodel>`).

An additional include `frts/vanillamodeldev` exists if you need to develope your own components... It contains the normal include and some additional headers like for component builder or the region interface.

## Interfaces

### Block

A block describes a certain point in the world consisting of the entities at this point. The default block interface only allows read access. For the purpose of developing custom block implementations there is a variant with write access. The later should never be used to change blocks outside the plugin.

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

### Model Factory

Utility module which acts as a factory to create model related objects like points, entities...

Load using `frts/ModelFactory` in the utilities section of the load file.

### Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.

### Region

The region consists of blocks at certain positions and represents the game world. It allows to set the position of entities in the world and retrieve them or whole blocks. 

### Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completly empty but at the same moment a block is requested for the first time it will be created by the generator.

### Region Manager

The region manager is the access interface to all region and resource managing related methods. It represents a data value containing the region. It also manages a list of changed positions since last reset. The will mostly be set automatically but can be also set by hand.

The region manager is implemented as an data value and can be accessed in the shared manager using the id `frts.vanillamodel.regionmanager`.

### Resource Lock

A resource lock prevents other entities from claiming a certain resource until it is released. Releasing can happen manually but also automatically if all instances of this lock are destroyed.  

### Resource Manager

The resource manager uses locks to manage access to resources by different entity groups. A entity group is only a fancy name for an id which is associated with a certain type of entities like a certain civilization. To find the nearest resource or entity with a certain resource it uses an algorithm to calculate the distance between the given position and the position of the resource. Currently this is the euclidian distance.  