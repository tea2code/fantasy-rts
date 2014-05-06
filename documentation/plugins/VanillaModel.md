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

## Point

A Point represents a 3D coordinate in the current region. It consists of x, y and z. It allows different mathematical operations. Because of it's pointer nature it's necessary to always dereference Point pointers before calling the operators. For example `p3 = *p1 + *p2` where `p1`, `p2` and `p3` are pointers to Points. This is not a perfect solution but currently i have no better idea. Maybe a wrapper class would help.