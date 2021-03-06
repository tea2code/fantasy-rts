# Configuration

The game data/configuration uses [YAML](http://www.yaml.org/) as file format. Read the official documentation for more information. It is important to note that in the following reference lists (structures beginning with an hyphen) are represented with only one item while they can have a unspecified number.

## ID, Namespace, Names

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

It is possible that an ID is specific to a certain state. This is indicated by a concatenated state string to the ID. The concatination is based on the template "state_id" defined in **Config Reference**. For example

    entity.dynamic.dwarf[north]

describes the dwarf entity facing north using the template "[{0}]" where "{0}" is replaced by north.

## Predefined IDs

Most of the IDs in this game can be modified as long as their usage is consistent. But there are a couple of IDs which are predefined and cannot change. They are used in the source code to create, modify and identify certain elements.

### Attributes:

- entity.attribute.moving.walk

### Keyboard Config:

- action.cursor_north
- action.cursor_south
- action.cursor_west
- action.cursor_east
- action.scroll_north
- action.scroll_south
- action.scroll_west
- action.scroll_east
- action.scroll_up
- action.scroll_down

### Entity States:

- north
- south
- east
- west
- up
- down
- stop

### Tasks:

See documentation for tasks.

### Decision Tree:

See documentation for decision nodes.

## Load Order File

In the mod directory is a file "mod.yaml". It describes which configuration files should be loaded and in which order. It can load complete directories (loading all files in it) or single files. Example:

    load:
        - game/
        - config/default.yaml
        - style

## Modifications

- *string*: A text value.
- *int*: An integer value.
- *optional*: This value is optional. If not set a value is always necessary.
- *id*: A namespace id of a entity. See **ID, Namespace, Names** for more information.
- *float*: A floating point value.
- *bool*: A boolean value.
- *?*: Any value type allowed.

### Style Reference:

    style:
        namespace: <string, "Namespace part.">

        tile_x: <int, optional, "The base size in x direction of one tile.">
        tile_y: <int, optional, "The base size in y direction of one tile.">
    
        images:
            namespace: <string, "Namespace part.">
            image:
                - name: <string, "Namespace end part.">
                  path: <string, "Path to the image.">
    
        sprites: 
            namespace: <string, "Namespace part.">
            image: <id, optional, "Default id of the image.">
            sprite: 
                - name: <string, "Namespace end part.">
                  image: <id, optional, "Id of the image.">
                  x: <int,  "X-coordinate of the sprite.">
                  y: <int, "Y-coordinate of the sprite.">
                - name: <string, "Namespace end part.">
                  image: <id, optional, "Id of the image.">
                  multiple: 
                    - x: <int,  "X-coordinate of the sprite.">
                      y: <int, "Y-coordinate of the sprite.">
                      chance: <float, "The chance that this sprite is selected.">
    
        mappings:
            namespace: <string, "Namespace part.">
            cursor: <id, "Mapping of cursor overlay.">
            default: <id, "Default mapping.">
            mapping:
                - name: <string, "Namespace end part.">
                  map: <id, "Map this id to...">
                  to: <id, "...this sprite.">

Both "sprites" and "sprite" can have the attributes "image", "width" and "height". One must always have them. If they are set on "sprites" they serve as default values for all "sprite" entities. Set on "sprite" they are individual for this entity and will override any values from "sprites".

The attribute "default" is the id of a sprite which will be used if no mapping is found.

Sprites can be defined in two ways. First you can directly declare the coordinates of it and create a single sprite. Or you can use "multiple" and define a list of coordinates of sprites of the same type. They will selected by chance based on the "chance" value. 

### Game Reference:

    game:
        size_x: <int, optional, "Size of game region in x direction.">
        size_y: <int, optional, "Size of game region in y direction.">

        mappings:
            race_player: <id, optional, "Race of the player.">
            food_plant: <id, optional, "Plant for food.">
            wood_plant: <id, optional, "Plant for wood.">
            tile_ground: <id, optional, "Ground tile.">
            tile_wall: <id, optional, "Wall tile.">

### Config Reference:

    config:
        fps: <int, optional, "Upper frames per second limit.">
        max_frame_time: <float, optional, "Maximum time between renders. The maximum time updating the state may take.">
        num_fps_avg: <int, optional, "Number of frames to keep for calculation fps.">
        render_decision_trees: <bool, optional, "If true decision trees are rendered to images.">
        scroll_width_x: <int, optional, "Number of coordinates to scroll in x direction.">
        scroll_width_y: <int, optional, "Number of coordinates to scroll in y direction.">
        state_id: <string, optional, "Template for state specific IDs.">
        view_x: <int, optional, "Size of viewport in x direction.">
        view_y: <int, optional, "Size of viewport in y direction.">
        window_title: <string, optional, "The window title. Currently it's possible to show the current fps in it.">

        keys:
            - action: <string, "ID of the action to execute.">
              key: <string, "Name of the key to press for this action.">

### Resources Reference:

    resources:
        namespace: <string, "Namespace part.">
        
        resources:
            namespace: <string, "Namespace part.">
            resource:
                - name: <string, "Namespace end part.">
                  type: <id, "The resource type.">
                  entity: <id, "The entity which is used to represent this resource after it is harvested.">
            
        types:
            namespace: <string, "Namespace part.">
            type:
                - name: <string, "Namespace end part.">

### Entity Reference:

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
                  resource: 
                      type: <id, optional, "Resource type.">
                      chance: <float, optional, "Chance that this resource appears.">

        tiles:
            namespace: <string, "Namespace part.">
            tile:
                - name: <string, "Namespace end part.">
                  blocking: 
                    - type: <id, "Blocking type. Must match attribute.">
            
### AI:

    ai:
        namespace: <string, "Namespace part.">

        tasks:
            namespace: <string, "Namespace part.">
            variance_min: <float, optional, "Default time variance minimum.">
            variance_max: <float, optional, "Default time variance maximum.">
            
            task:
                - name: <string, "Namespace end part.">
                  type: <id, "Task type id.">
                  variance_min: <float, optional, "Time variance minimum.">
                  variance_max: <float, optional, "Time variance maximum.">
                  in: <string, optional, "Input parameter for pipelines.">
                  out: <string, optional, "Output parameter for pipelines.">
                  ...

            decisions:
                namespace: <string, "Namespace part.">
                
                decision:
                    - namespace: <string, "Namespace part.">
                      entity: <id, optional, "Name of entity for which this decision tree is.">
                      start_node: <id, optional, "Id of root node.">
                      tree:
                        - name: <string, "Namespace end part.">
                          type: ai.decision.node.random <id, "Random node type id.">
                          success: <id, optional, "Node in case of success.">
                          fail: <id, optional, "Node in case of failure.">
                          next: <id, optional, "If result of task doesn't matter this node will be executed.">
                          ...

Both "tasks" and "task" can have the attributes "variance_min" and "variance_max". One must always have them. If they are set on "tasks" they serve as default values for all "task" entities. Set on "task" they are individual for this entity and will override any values from "tasks".

The three values "success", "fail" and "next of task nodes are completly optional. If none is defined the node is a leaf and the tree ends after this node.

For a detailed explanation of all task and decision node types see the according documentation files.