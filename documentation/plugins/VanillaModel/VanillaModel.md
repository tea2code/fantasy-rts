# Vanilla Model

Represents the data model. Gives access to the region consisting of blocks in a 3D world. Defines entities and allows search for resources.

## Installation

Default path of plugin is `vanilla-model/vanilla-model`.

## Dependencies

- VanillaEvent

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillamodel` (e.g. `#include <frts/vanillamodel>`).

An additional include `frts/vanillamodeldev` exists if you need to develope your own components... It contains the normal include and some additional headers like for component builder or the region interface.

## Thread safety

Currently following parts are thread safe:

- Block
- Region Manager

By thread safety is acquired using a mutex. Normally a `std::recursive_mutex` is used. But it can be replaced by a lightweight spin lock implementation by adding `DEFINES+=SPIN_LOCK` to the additional arguments of qmake. Spin lock is [implemented using a simple atomic boolean](http://stackoverflow.com/a/8115400/1931663).

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

### Event

Some model related event values for **VanillaEvent** are added to the event manager. The ids can be also found in the static class `ModelEventIds`.

- **EntityEventValue:** An event value for entities. Has type `frts.vanillamodel.event.value.entity`.
- **EntityListEventValue:** An event value for entity lists. Has type `frts.vanillamodel.event.value.entity.list`.
- **PointEventValue:** An event value for points. Has type `frts.vanillamodel.event.value.point`.
- **PointListEventValue:** An event value for point lists. Has type `frts.vanillamodel.event.value.point.list`.

### Model Data

Model related meta settings like the size of the map are stored in this data value. 

Default ID can be found in the static class `ModelIds`.

Will identify itself by the name and type `frts::ModelData`.

### Model Factory

Utility module which acts as a factory to create model related objects like points, entities... The method `init()` will wait one execution to allow other modules to override implementations (for example replacing the original region with another using `setRegion()`).

Load using `frts/ModelFactory` in the `utilities` section of the load file. This is also the utility ID. It can be found in the static class `ModelIds`. 

Will identify itself by the name and type `frts::ModelFactory`. It can also be found in the static class `ModelIds`. 

The model factory contains following types of methods:

- Getter to access different special purpose helper classes. Currently getter exist for distance algorithm, path finder and map parser.
- Maker/Builder methods to create components, entities (empty and preconfigurated) and points.
- Map parser and component builders (for creating components) can be registered.
- While all of the above methods have already predefined classes/objects they can be replaced using the setters. Most of the setters must be called before `init()`. A couple of setters are also for replacing internal values like the region manager.

### Model Reseter

The model reseter handles model related clean up at the end of each frame. It should be placed as the last render module. Currently the following resets are done:

- Reset changed positions.

Load using `frts/ModelReseter` in the `renderModule` section of the load file.

Will identify itself by the name and type `frts::ModelReseter`.

### Model Startup

The model startup handles model related startup code. It should be executed as a startup module. Currently the following tasks are executed:

- Precalculated configured z-levels.

Load using `frts/ModelStartup` in the `startupModules` section of the load file.

Will identify itself by the name and type `frts::ModelStartup`.

### Path Finder

The path finder obtained by the model factory allows to calculate the shortest path between two points in the region. The default implementation uses A* with Manhattan distance. It also supports the teleport component by adding the target position to the list of possible neighbors.

#### Possible ideas for optimization of default implementation

- Before calculating a path from start to goal, try to calculate a path with limited number of iterations from goal to start. If a path is found use it. If goal is in a small room we see that there is no possible path and can stop the whole algorithm. This may prevent some "flooding the whole map" cases and even is realistic because start and goal are often blocked if they are in rooms with closed doors. Maybe it's even possible to use the already calculated values.
- [Near-Optimal Hierarchical Pathfinding (HPA*)](http://aigamedev.com/open/review/near-optimal-hierarchical-pathfinding/)
- Another priority queue like a heap. For example Boost provides a heap implementation with support for priority updates.
- Simplify grid graph with something like a navigation mesh. It's probably possible to connect positions inside of rooms and handle them as a "single" way point.

##### Tested and discarded

- A faster variant of makePoint() similar to makeId(). This failed because calculating a key was way to slow. Tested with string key and pairing function.
- Calculate path from goal to start which removes the need for std::reverse(). Not much difference.

### Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations.

### Region

The region consists of blocks at certain positions and represents the game world. It allows to set the position of entities in the world and retrieve them or whole blocks. 

### Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completely empty but at the same moment a block is requested for the first time it will be created by the generator.

See [RegionGenerator.md](RegionGenerator.md) for more information.

### Region Manager

The region manager is the access interface to all region and resource managing related methods. It represents a data value containing the region. It also manages a list of changed positions since last reset. The will mostly be set automatically but can be also set by hand.

Until phase **Initialize Modules** it is possible to set and change the used implementation of different sub systems like the resource managers or the region generator in the model factory. The model factory will even wait a first iteration of `init()` before initializing. The default implementations are used if no others are set.

The region manager is implemented as an data value and can be accessed via the shared manager. 

Default ID can be found in the static class `ModelIds`.

Will identify itself by the name and type `frts::RegionManager`.

**IMPORTANT:** Because of implementation details it is currently not possible to access the region manager before initialization of modules after phase **Initialize Modules** is complete. Doing so will most likely result in a crash or undefined behavior.

### Resource Lock

A resource lock prevents other entities from claiming a certain resource until it is released. Releasing can happen manually but also automatically if all instances of this lock are destroyed.  

### Resource Manager

The resource manager uses locks to manage access to resources by different entity groups. A entity group is only a fancy name for an id which is associated with a certain type of entities like a certain civilization. To find the nearest resource or entity with a certain resource it uses an algorithm to calculate the distance between the given position and the position of the resource. 

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

The region config allows to set the size of the map in x and y direction. Additionally it is possible to precalculate several z-levels up and down from the start. This allows a better performance because these z-levels will be already existing if accessed. Use the following keys to do so:

    region:
        
        surface_level: <integer, optional, default 0>
        
        width: <integer greater 0>
        height: <integer greater 0>
        
        precalculate_up: <integer greater/equal 0, optional>
        precalculate_down: <integer greater/equal 0, optional>