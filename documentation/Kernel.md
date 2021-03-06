# Kernel

The kernel or core consists only of a couple of classes defining the plugin architecture and the shared data. All game implementation related stuff exists in external plugins.

## Configuration

The configuration package contains classes related to reading and parsing configuration files. Current implementation uses the YAML format. The configuration object has ja simple generic interface to access values in the configuration files. Depending on the unterlaying format not all format specific details may be supported. It can be accessed through the shared manager. 

### YAML

YAML is an file format with a similar syntax to languages like Python and Perl. For more information see the [Homepage](http://yaml.org/) and [Wikipedia](https://en.wikipedia.org/wiki/YAML). Because of the configuration interface not every aspect of YAML is supported.

#### Boolean

    key: true or false

#### Floating point number

Integers are also valid floating point numbers.

    key: 1 or 1.2

#### Integer number

    key: 1

#### String

Strings containing whitespace must be encapsulated in quotes. The current convention is to encapsulate readable text in quotes and strings which for example represent IDs not. The latter shouldn't (by convention) contain whitespace. This allows a easy differentiation between human readable text and configuration strings.

    key: text or "text with whitespace"

#### List of x

Every type can be represented as a list. 

    key:
        - value1
        - value2

## FRTS

This package consists of include files which allow an easier usage of the other packages. The best way to use this in external projects like plugins is to add the *src* directory to the include path and use the kernel packages with the following includes:

    #include <frts/configuration>
    #include <frts/log>
    #include <frts/module>
    #include <frts/plugin>
    #include <frts/shared>

These include files only contain classes... which are useful in external projects.

## Log

The log package contains implementations of loggers. Currently Easylogging++ is used. The log object has a simple interface to create a log message. It can be accessed through the shared manager. A log message consists of a (hopefully) unique name for the module (for example the plugin module name) and the message. The configuration and the output files are stored in the directory *log*. Example:

    log->debug("Kernel", "Hello World");

This would output a message similar to

    23/03/2014 11:05:45,279295 - DEBUG - Kernel - Hello World

The supported log levels are in order of their verbosity:

- **Debug:** Use only for development related messages. Normally disabled in release builds.
- **Info:** Standard level for non critical messages. Normally disabled in major stable builds.
- **Warning:** Use for important messages which aren't critical as errors. Always active.
- **Error:** Use for exception and error messages. Always active.

## Main

### main.cpp

Puts everything together. You can manipulate the base settings using command line arguments. For example `fantasy-rts.exe help` will print the command line options help. To reset the length of one frame to 42 milliseconds use `fantasy-rts.exe deltaTime 42`. Following are all supported arguments:

- **help:** Produce command line argument help message.                   
- **deadLock:** Number of extra executions for modules before a dead lock is assumed.
- **deltaTime:** Set length of one frame in milliseconds.                          
- **loadFile:** File name of load file relative to plugins root.                               
- **logConfigFile:** Path to log config file.                       
- **maxFrameTime:** Maximum length of a frame in milliseconds.                    
- **pluginsRoot:** Path to plugins root directory.                        

### Application

The application class executes all the execution phase related functions and is mostly a collection of more or less unrelated methods.

### IteratorWrapper

Simple wrapper for iterator pointer which allows usage of interfaces in iterators.

## Module

The module package contains all module related interfaces and some additional classes like for error handling related to modules. 

### Interface "Module"

This is the base interface for all modules. It defines methods related to the execution phases of the application.

### Interface "Tickable"

A module which implements this interface can be called every frame with the current application state. Tickable modules represent the brain of this application.

### Interface "Utility"

Utility modules aren't automatically called but can be called by other modules. They represent common functions offered by plugins.

### Module Identification

To identify if a certain module is available there are four useful methods which every module must implement:

- **getName:** The name of an individual implementation of a certain module.
- **getVersion:** The version of an individual implementation of a certain module.
- **getTypeName:** The type of an module describes it public interface. There may be several implementation of an module type. In most cases it is recommended to check for the type name. 
- **getTypeVersion:** The type version of an module. This number should change if the interface is changed.

Following is an minimal example for checking if a utility is available and has the right version.

    try
    {
        UtilityPtr module = getUtility<Utility>(shared, CommandIds::commandFactory());
        if (module->getTypeVersion() != 1)
        {
            throw ModuleViolation("Utility CommandFactory has the wrong version.");
        }
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

Note that it doesn't cast to `CommandFactory` but to general `Utility` type to prevent a possible problem with an incompatible cast. Checking update or render modules can be done by iterating over them and checking for the correct type name and version.

For much easier use the functions `frts::validateUtility()` and `frts::validateTickable()` where definied in the kernel and are accessible using `#include <frts/module>`. It is recommended to use these.

## Plugin

The plugin package consists of two parts. First is the interface and API for individual plugins. Every plugin library must have one class which implements the plugin interface. Additionally in some place in the library the plugin API must be included and the implemented plugin class must be registered using the method `REGISTER_PLUGIN(<Name-Of-Plugin-Class>)`. This is all to create a plugin. Of course every plugin library should implement modules or else the plugin will nevery do anything. Every plugin library contains also a version method (defined in the plugin API) which returns the implemented plugin API version. In the unlikely case that the plugin API will change someways this version is used to determine incompatibilities. 

The second part of the package is the plugin loading related code which is only used inside the kernel. It consists of a plugin manager and a platform independent library loader. The plugin loading mechanism allows to load regular plugin libraries but also any generic library. This is helpful if a plugin is linked to a dynamic library. In this case the dynamic library must be loaded before the plugin.

## Shared

The shared package contains the shared manager which represents the application state. It contains data values and all existing modules. Every frame the modules receive the current state. While it may be tempting to store the shared manager inside the module you must never do this. It will probably work but there is no guarantee that a single instance of this manager stays valid. Following state data can be accessed through the manager:

### Data Values

Data values store all variable game state data. They implement the same identification methods as modules.

#### MainData

This data value contains data provided by the main program. This is mostly environment related information. 

Default ID can be found in the static class `MainIds`.

Will identify itself by the name and type `frts::MainData`.

### Frame

The frame object contains meta information about the current frame. This includes the time since the last frame, the frame number and the passed time since the game start. If you need to schedule something in the future you should prefer the time since game start instead of the frame number. While it may be easier to use the frame number there is no guarantee that every frame has the same length. By using the time even on the slower computer the internal game speed stays (nearly) the same.

### ID Generator

The function *makeId()* generates a new id with the given string. 

A possible faster implementation can be activated using `DEFINES+=FRTS_FAST_ID` in the additional arguments of qmake. Performance advantage is tested using the *A\* Benchmark* (see **A-Star Benchmark.md**). The difference in the benchmark was not much but it was measurable and will be much larger in other cases.

### Log

The current logger. See **Log** for more information.

### Render Modules

The currently used render modules. See **Modules** for more information.

### Update Modules

The currently used update modules. See **Modules** for more information.

### Utilities

Available utilities. See **Modules** for more information.

## Test

The (unit) test package of the kernel. 