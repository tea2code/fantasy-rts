# Fantasy-RTS

A fantasy real-time strategy game in the style of Dwarf Fortress. For now without a name.

## Roadmap

Current Version: **6**

- Version 1: Basic framework with simple demo level.
- Version 2: Basic creature with simple behaviour related to food.
- Version 3: Read all ingame configuration from files. 
- Version 4: Ingame resource system.
- Version 5: Data structure for maps, resources, entities...
- Version 6: Task system. Fast pathfinding.
- Version 7: More generic configuration.
- Version 8: Support für multiple sprites per entity and unregular sized sprites.
- Version 9: Refactoring. Working shrubs. Better GotoTask.

## Coming Soon

Following features are planned for the near future.

- Sidebar with info about selected entity, commands and some kind of global info.
- Mouse and Keyboard commands.
- Collect food.
- Collect wood and build walls.
- Direct control of creatures.

## Attribution

- Test sprites by [Sharm](http://opengameart.org/content/16x16-overworld-tiles)

## Manual

The game data/configuration uses [YAML](http://www.yaml.org/) as file format. Read the official documentation for more information. It is important to note that in the following reference lists (structures beginning with an hyphen) are represented with only one item while they can have a unspecified number.

### ID, Namespace, Names

The variable *namespace* describes a namespace path of a certain entity. For every entity exists a *name* which togheter with the namespace is unique and forms the *id*. Multiple namespace path parts including the name become joined by a dot.

Example:

    style:
        namespace: style
        
        sprites:
            namespace: sprite
            sprite:
                - name: dwarf
                  ...

This describes a sprite entity with the *name* "unknown" in the *namespace* "sprite" which itself is in the *namespace* "style". This means the full id of this sprite entity is "style.sprite.unknown". 

The ID is used to link different data and check if a value already exists and should be overriden. For implementation reasons this may not always be the case. But that can change any time. This means always define namespace and name as specified in the following references.

### Modifications

- *string*: A text value.
- *int*: An integer value.
- *optional*: This value is optional. If not set a value is always necessary.
- *id*: A namespace id of a entity. See **ID, Namespace, Names** for more information.
- *float*: A floating point value.
- []: List of values.

#### Style Reference:

    style:
        namespace: <string, "Namespace part.">

        tile_x: <int, "The base size in x direction of one tile.">
        tile_y: <int, "The base size in y direction of one tile.">
    
        images:
            namespace: <string, "Namespace part.">
            image:
                - name: <string, "Namespace end part.">
                  path: <string, "Path to the image.">
    
        sprites: 
            namespace: <string, "Namespace part.">
            image: <id, optional, "Id of the image.">
            width: <int, optional, "Width of the sprite.">
            height: <int, optional, "Height of the sprite.">
            sprite: 
                - name: <string, "Namespace end part.">
                  image: <id, optional, "Id of the image.">
                  x: <int, "X-coordinate of the sprite.">
                  y: <int, "Y-coordinate of the sprite.">
                  width: <int, optional, "Width of the sprite.">
                  height: <int, optional, "Height of the sprite.">
    
        mappings:
            namespace: <string, "Namespace part.">
            default: <id, "Default mapping.">
            mapping:
                - name: <string, "Namespace end part.">
                  map: <id, "Map this id to...">
                  to: <id, "...this sprite.">

Both "sprites" and "sprite" can have the attributes "image", "width" and "height". One must always have them. If they are set on "sprites" they serve as default values for all "sprite" entities. Set on "sprite" they are individual for this entity and will override any values from "sprites".

The attribute "default" is the id of a sprite which will be used if no mapping is found.

The types "sprite", "image" and "mapping" can/should/will exist multiple times. Each representing a single entity.

#### Game Reference:

    game:
        size_x: <int, "Size of game region in x direction.">
        size_y: <int, "Size of game region in y direction.">

#### Config Reference:

    config:
        fps: <int, "Upper frames per second limit.">
        max_frame_time: <float, "Maximum time between renders. The maximum time updating the state may take.">
        scroll_width_x: <int, "Number of coordinates to scroll in x direction.">
        scroll_width_y: <int, "Number of coordinates to scroll in y direction.">
        view_x: <int, "Size of viewport in x direction.">
        view_y: <int, "Size of viewport in y direction.">
        window_title: <string, "The window title. Currently it's possible to show the current fps in it.">

#### Resources Reference:

    resources:
        namespace: <string, "Namespace part.">
        
        resources:
            namespace: <string, "Namespace part.">
            resource:
                - name: <string, "Namespace end part.">
                  type: <id, "The resource type.">
                  value: <float, "The value of this resource aka units.">
            
        types:
            namespace: <string, "Namespace part.">
            type:
                - name: <string, "Namespace end part.">

The types "resource" and "type" can/should/will exist multiple times. Each representing a single entity.

#### Entity Reference:

    entity:
        namespace: <string, "Namespace part.">
        
        attributes:
        namespace: <string, "Namespace part.">
            category:
                - namespace: <string, "Namespace part.">
                    attribute:
                        - name: <string, "Namespace end part.">

        dynamics:
            namespace: <string, "Namespace part.">
            dynamic:
                - name: <string, "Namespace end part.">
                  blocked: 
                    - type: <id, "Blocked type. Must match attribute.">
                  moving:
                    - type: <id, "Moving type. Must match attribute.">
                      speed: <float, "Speed of this type of moving.">

        statics:
            namespace: <string, "Namespace part.">
            static:
                - name: <string, "Namespace end part.">
                  blocked: 
                    - type: <id, "Blocked type. Must match attribute.">
                  blocking: 
                    - type: <id, "Blocking type. Must match attribute.">
                  resource: <id, optional>
                  resource_chance: <float, optional>

        tiles:
            namespace: <string, "Namespace part.">
            tile:
                - name: <string, "Namespace end part.">
                  blocking: 
                    - type: <id, "Blocking type. Must match attribute.">
            
The types "attribute", "dynamic", "static", "tile", "blocked", "blocking" and "moving" can/should/will exist multiple times. Each representing a single entity.