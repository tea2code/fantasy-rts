# Fantasy-RTS

A fantasy real-time strategy game in the style of Dwarf Fortress. For now without a name.

## Roadmap

Current Version: **5**

- Version 1: Basic framework with simple demo level.
- Version 2: Basic creature with simple behaviour related to food.
- Version 3: Read all ingame configuration from files. 
- Version 4: Ingame resource system.
- Version 5: Data structure for maps, resources, entities...
- Version 6: Task system. Collect and use food.
- Version 7: Support für multiple sprites per entity and unregular sized sprites.
- Version ?: More generic configuration.

## Coming Soon

Following features are planned for the near future.

- Sidebar with info about selected entity, commands and some kind of global info.
- Basic animation.
- Mouse and Keyboard commands.
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
                - name: unknown
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
        namespace: <string>

        tile_x: <int>
        tile_y: <int>
    
        images: <optional>
            namespace: <string>
            image:
                - name: <string>
                  path: <string>
    
        sprites: <optional>
            namespace: <string>
            image: <id, optional>
            width: <int, optional>
            height: <int, optional>
            sprite: 
                - name: <string>
                  image: <id, optional>
                  x: <int>
                  y: <int>
                  width: <int, optional>
                  height: <int, optional>
    
        mappings: <optional>
            namespace: <string>
            default: <id>
            mapping:
                - name: <string>
                  map: <id>
                  to: <id>

Both "sprites" and "sprite" can have the attributes "image", "width" and "height". One must always have them. If they are set on "sprites" they serve as default values for all "sprite" entities. Set on "sprite" they are individual for this entity and will override any values from "sprites".

The attribute "default" is the id of a sprite which will be used if no mapping is found.

The types "sprite", "image" and "mapping" can/should/will exist multiple times. Each representing a single entity.

#### Game Reference:

    game:
        size_x: <int>
        size_y: <int>

#### Config Reference:

    config:
        fps: <int>
        max_frame_time: <float>
        scroll_width_x: <int>
        scroll_width_y: <int>
        view_x: <int>
        view_y: <int>
        window_title: <string>

#### Resources Reference:

    resources:
        namespace: <string>
        
        resources:
            namespace: <string>
            resource:
                - name: <string>
                  type: <string>
                  value: <float>
            
        types:
            namespace: <string>
            type:
                - name: <string>
                  type_name: <string>

The types "resource" and "type" can/should/will exist multiple times. Each representing a single entity.

#### Entity Reference:

    entity:
        namespace: <string>
        
        attributes:
        namespace: <string>
            attribute-category:
                - namespace: <string>
                    attribute:
                        - name: <string>

        dynamics:
            namespace: <string>
            dynamic:
                - name: <string>
                  blocked: [<string>]
                  speed: <float>

        statics:
            namespace: <string>
            static:
                - name: <string>
                  blocked: [<string>]
                  blocking: [<string>]
                  resource: <string, optional>
                  resource_chance: <float, optional>

        tiles:
            namespace: <string>
            tile:
                - name: <string>
                  blocking: [<string>]
            
The types "attribute", "dynamic", "static" and "tile" can/should/will exist multiple times. Each representing a single entity.