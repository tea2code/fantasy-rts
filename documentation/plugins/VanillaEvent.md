# Vanilla Event

This plugin implements a variant of the [Observer-Pattern](https://en.wikipedia.org/wiki/Observer_pattern). It allows to send and receive events outside the normal main loop. While this feature is helpful in a lot of cases it should never be used to completely avoid the main loop. Recommended use is receiving the event, storing it and handle it later in the `tick()` method. 

## Installation

Default path of plugin is `vanilla-event/vanilla-event`.

## Dependencies

No special dependency.

## Development

Access to all necessary interfaces can be acquired by adding the source directory to the include paths and include `frts/vanillaevent` (e.g. `#include <frts/vanillaevent>`).

## Interfaces

### Event

Events are simple containers which consists of their type id and a couple of event values. The type id is the same as the one used in the `subscribe()` method of the event manager. An observer can check this id to decide what to do with an event. 

### Event Manager

The event manager is implemented as a utility module. 

Load using `frts/EventManager` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::EventManager`. It can also be found in the static class `EventIds`. 

### Event Observer

Any class which want to register to any event must implement the event observer interface. It has only one method  `notify()` which is called if an event has been raised. 

### Event Value

An event value stores data associated with an event. Every event value has a type which allows to identify what underlying variable type is used. The type is also used to create these values using the appropriate make methods in event manager. Following event values are provided others can be registered in the event manager. The ids can be also found in the static class `EventIds`.

- **StringEventValue:** An event value for strings. Has type `frts.vanillaevent.value.string`.
- **StringListEventValue:** An event value for string lists. Has type `frts.vanillaevent.value.string.list`.
- **IntegerEventValue:** An event value for integers (implemented as `long`). Has type `frts.vanillaevent.value.integer`.
- **IntegerListEventValue:** An event value for integer (implemented as `long`) lists. Has type `frts.vanillaevent.value.integer.list`.
- **FloatEventValue:** An event value for floating point numbers (implemented as `double`). Has type `frts.vanillaevent.value.float`.
- **FloatListEventValue:** An event value for floating point number (implemented as `double`) lists. Has type `frts.vanillaevent.value.float.list`.
- **BooleanEventValue:** An event value for booleans. Has type `frts.vanillaevent.value.boolean`.
- **BooleanListEventValue:** An event value for boolean lists. Has type `frts.vanillaevent.value.boolean.list`.
- **IdEventValue:** An event value for ids. Has type `frts.vanillaevent.value.id`.
- **IdListEventValue:** An event value for id lists. Has type `frts.vanillaevent.value.id.list`.

### Event Value Builder

Builder create event values and can be registered at the factory. They are identified by an ID and it is possible to create variants of event values by registering the same builder with different settings.