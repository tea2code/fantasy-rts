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

Components describe the attributes, abilities... of a entity. Their default IDs can be found in the static class `ComponentIds`.

See [Components.md](Components.md) for more information.

### Component Builder

Components are created using builders which can be registered at the model factory.

### Entity

Entities represent all interactable objects in the world. They consist of components representing their abilities, attributes...

### Model Data

Model related meta settings like the size of the map are stored in this data value. 

Default ID can be found in the static class `ModelIds`.

Will identify itself by the name and type `frts::ModelData`.

### Model Factory

Utility module which acts as a factory to create model related objects like points, entities...

Load using `frts/ModelFactory` in the `utilities` section of the load file. This is also the utility ID. It can be found in the static class `ModelIds`. 

Will identify itself by the name and type `frts::ModelFactory`. It can be also found in the static class `ModelIds`. 

### Model Reseter

The model reseter handles model related clean up at the end of each frame. It should be placed as the last render module. Currently the following resets are done:

- Reset changed positions.

Load using `frts/ModelReseter` in the `renderModule` section of the load file.

Will identify itself by the name and type `frts::ModelReseter`.

### Path Finder

The path finder optained by the model factory allowes to calculate the shortest path between two points in the region. The default implementation uses A* with manhattan distance. It also supports the teleport component by adding the target position to the list of possible neighbors.

#### Possible ideas for optimization of default implementation

- Before calculating a path from start to goal, try to calculate a path with limited number of iterations from goal to start. If a path is found use it. If goal is in a small room we see that there is no possible path and can stop the whole algorithm. This may prevent some "flooding the whole map" cases and even is realistic because start and goal are often blocked if they are in rooms with closed doors. Maybe it's even possible to use the already calculated values.
- [Near-Optimal Hierarchical Pathfinding (HPA*)](http://aigamedev.com/open/review/near-optimal-hierarchical-pathfinding/)
- Another priority queue like a heap. For example Boost provides a heap implementation with support for priority updates.
- Simplify grid graph with something like a navigation mesh. It's probably possible to connect positions inside of rooms and handle them as a "single" waypoint.

##### Tested and discarded

- A faster variant of makePoint() similar to makeId(). This failed because calculating a key was way to slow. Tested with string key and pairing function.
- Calculate path from goal to start which removes the need for std::reverse(). Not much difference.

### Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.

### Region

The region consists of blocks at certain positions and represents the game world. It allows to set the position of entities in the world and retrieve them or whole blocks. 

### Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completly empty but at the same moment a block is requested for the first time it will be created by the generator.

See [RegionGenerator.md](RegionGenerator.md) for more information.

### Region Manager

The region manager is the access interface to all region and resource managing related methods. It represents a data value containing the region. It also manages a list of changed positions since last reset. The will mostly be set automatically but can be also set by hand.

Until phase 10 it is possible to set and change the used implementation of different sub systems like the resource managers or the region generator in the model factory. The model factory will even wait a first iteration of `init()` before initializing. The default implementations are used if no others are set.

The region manager is implemented as an data value and can be accessed via the shared manager. 

Default ID can be found in the static class `ModelIds`.

Will identify itself by the name and type `frts::RegionManager`.

**IMPORTANT:** Because of implementation details it is currently not possible to access the region manager before initalization of modules after phase 10 is complete. Doing so will most likely result in a crash or undefined behavior.

### Resource Lock

A resource lock prevents other entities from claiming a certain resource until it is released. Releasing can happen manually but also automatically if all instances of this lock are destroyed.  

### Resource Manager

The resource manager uses locks to manage access to resources by different entity groups. A entity group is only a fancy name for an id which is associated with a certain type of entities like a certain civilization. To find the nearest resource or entity with a certain resource it uses an algorithm to calculate the distance between the given position and the position of the resource. Currently this is the euclidian distance.  

## Configuration

### Components

See [Components.md](Components.md) for more information.

### Entities

Entities configuration consists of a list of entities. Every entity has an ID and a list of components. The ID consists of a global `namespace` and a `name` part. The namespace is prefixed to the name and together they form the ID. A component has a attribute `component` with the full ID and a variable list of component specific attributes. It's possible to define a entity in several files. The final entity will contain all components.

    entities:
        namespace: <string>
        
        entities:
            - name: <string>
              components:
                - component: <string representing an id>
                  ...

The main key is `entities`.

### Region

The region config allows to set the size of the map in x and y direction. Use the following keys to do so:

    region:
        
        width: <integer greater 0>
        height: <integer greater 0>