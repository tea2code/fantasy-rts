# Components

Components describe the attributes, abilities... of a entity. Their default IDs can be found in the static class `ComponentIds`.

## BlockedBy

Entities have the ability to block other entities. BlockedBy describes by what a entity is blocked.

### Configuration

    blocks:
        - <string representing an id>

## Blocking

Entities have the ability to block other entities. Blocking describes what a entity blocks.

### Configuration

    blocks:
       - <string representing an id>

## Drop

Entities can drop other entities if they are destroyed, killed, harvested... The dropable entities are defined by this component.

### Configuration

    drops:
        - <string representing an entity id>

## HasResource

Entities may contain resources which can be harvested.

### Configuration

    resources:
        - <string representing an id>

## IsResource

Entities with this component represent a resource.

### Configuration

    resource_type: <string representing an id>

## Movable

Entities with this component can move and may change the direction they are looking.

## SortOrder

Entities may have a certain order in a block. The sort order component stores this attribute.

In code are a couple of sort orders predefined:

- Default: -1
- Tile Default: 0
- Tile Normal: 40
- Tile Important 80
- Static Default: 100
- Static Normal: 140
- Static Important: 180
- Dynamic Default: 200
- Dynamic Normal: 240
- Dynamic Important: 280
- Overlay Default: 300
- Overlay Normal: 380
- Overlay Important: 380
- Bottom: -1000
- Top: 1000

### Configuration

    sort_order: <integer>

## Teleport

This component indicates a connection between its entity and another entity. For example can be used for portals or slopes. 