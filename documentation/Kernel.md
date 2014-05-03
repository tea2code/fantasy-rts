# Kernel

The kernel or core consists only of a couple of classes defining the plugin architecture and the shared data. All game implementation related stuff exists in external plugins.

## Configuration

The configuration package contains classes related to reading and parsing configuration files. Current implementation uses the YAML format. The configuration object has ja simple generic interface to access values in the configuration files. Depending on the unterlaying format not all format specific details may be supported. It can be accessed through the shared manager. 

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

Puts everything together. You can manipulate the base settings using command line arguments. For example `fantasy-rts.exe help` will print the command line options help. To reset the length of one frame to 42 use `fantasy-rts.exe deltaTime 42`.

### Application

The application class executes all the execution phase related functions and is mostly a collection of more or less unrelated methods.

### IteratorWrapper

Simple wrapper for iterator pointer which alows usage of interfaces in iterators.

## Module

The module package contains all module related interfaces and some additional classes like for error handling related to modules. Every module has a name. If it is necessary that a module is associated with an id the id is created from this name (for example utility modules).

### Interface "Module"

This is the base interface for all modules. It defines methods related to the execution phases of the application.

### Interface "Tickable"

A module which implements this interface can be called every frame with the current application state. Tickable modules represent the brain of this application.

### Interface "Utility"

Utility modules aren't automatically called but can be called by other modules. They represent common functions offered by plugins.

## Plugin

The plugin package consists of two parts. First is the interface and API for individual plugins. Every plugin library must have one class which implements the plugin interface. Additionally in some place in the library the plugin API must be included and the implemented plugin class must be registered using the method `REGISTER_PLUGIN(<Name-Of-Plugin-Class>)`. This is all to create a plugin. Of course every plugin library should implement modules or else the plugin will nevery do anything. Invisible every plugin library contains also a version method (defined in the plugin API) which returns the implemented plugin API version. In the unlikely case that the plugin API will change somedays this version is used to determine incompatibilities. 

The second part of the package is the plugin loading related code which is only used inside the kernel. It consists of a plugin manager and a platform independent library loader.

## Shared

The shared package contains the shared manager which repesents the application state. It contains data values and all existing modules. Every frame the modules receive the current state. While it may be tempting to store the shared manager inside the module you must never do this. It will probably work but there is no guarantee that a single instance of this manager stays valid. Following state data can be accessed through the manager:

### Data Values

Data values store all variable game state data. 

### Frame

The frame object contains meta information about the current frame. This includes the time since the last frame, the frame number and the passed time since the game start. If you need to schedule something in the future you should prefer the time since game start instead of the frame number. While it may be easier to use the frame number there is no guarantee that every frame has the same length. By using the time even on the slower computer the internal game speed stays (nearly) the same.

### ID Generator

The function *makeId()* generates a new id with the given string. This function may implement optimizations like caches and similar functions.

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