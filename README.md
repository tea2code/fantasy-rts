# Fantasy-RTS

A fantasy real-time strategy game in the style of Dwarf Fortress. For now without a name.

## Versions

Current Version: **2**

- Version 1: Basic framework with simple demo level.
- Version 2: Basic creature with simple behaviour related to food.
- Version 3: Read all ingame configuration from files. 
- Version 4: Ingame resource system.
- Version 5: Task system. Collect and use food.

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

### ID, Namespace, Names

The variable *namespace* describes a namespace path of a certain entity. For every entity exists a *name* which togheter with the namespace is unique and forms the *id*. Multiple namespace path parts including the name become joined by a dot.

Example:

```YAML
style:
    namespace: style
    
    sprites:
        namespace: sprite

        sprite:
            name: unknown
            ...
```

This describes a sprite entity with the *name* "unknown" in the *namespace* "sprite" which is in the *namespace* "style". This means the full id of this sprite entity is "style.sprite.unknown". 

### Modifications

- *string*: A text value.
- *int*: An integer value.
- *optional*: This value is optional. If not set a value is always necessary.
- *id*: A namespace id of a entity. See **ID, Namespace, Names** for more information.

#### Style Reference:

```YAML
style:
    namespace: <string>

    images:
        namespace: <string>
        
        image:
            name: <string>
            path: <string>

    sprites:
        namespace: <string>
        image: <id, optional>
        width: <int, optional>
        height: <int, optional>

        sprite:
            name: <string>
            image: <id, optional>
            x: <int>
            y: <int>
            width: <int, optional>
            height: <int, optional>

    mappings:
        namespace: <string>
        default: <id>

        mapping:
            name: <string>
            map: <id>
            to: <id>
```

Both "sprites" and "sprite" can have the attributes "image", "width" and "height". One must always have them. If they are set on "sprites" they serve as default values for all "sprite" entities. Set on "sprite" they are individual for this entity and will override any values from "sprites".

The attribute "default" is the id of a sprite which will be used if no mapping is found.