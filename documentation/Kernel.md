# Kernel

The kernel or core consists only of a couple of classes defining the plugin architecture and the shared data. All game implementation related stuff exists in external plugins.

## main.cpp

Puts everything together.

## Application

The application class executes all the execution phase related functions and is mostly a collection of more or less unrelated methods.

## IteratorWrapper

Simple wrapper for iterator pointer which alows usage of interfaces in iterators.

## Configuration

The configuration package contains classes related to reading and parsing configuration files. Current implementation uses the YAML format. The configuration object has ja simple generic interface to access values in the configuration files. Depending on the unterlaying format not all format specific details may be supported. It can be accessed through the shared manager. 

## Log

The log package contains implementations of loggers. Currently Easylogging++ is used. The log object has a simple interface to create a log message. It can be accessed through the shared manager. A log message consists of a (hopefully) unique name for the module (for example the plugin module name) and the message. The configuration and the output files are stored in the directory log. Example:

    log->debug("Kernel", "Hello World");

This would output a message similar to

    23/03/2014 11:05:45,279295 - DEBUG - Kernel - Hello World

The supported log levels are in order of their verbosity:

- **Debug:** Use only for development related messages. Normally disabled in release builds.
- **Info:** Standard level for non critical messages. Normally disabled in major stable builds.
- **Warning:** Use for important messages which aren't critical as errors. Always active.
- **Error:** Use for exception and error messages. Always active.

## Module

The module package contains all module related interfaces and some additional classes like for error handling related to modules. Every module has a name. If it is necessary that a module is associated with an id the id is created from this name (for example utility modules).

### Interface "Module"

This is the base interface for all modules. It defines methods related to the execution phases of the application.

### Interface "Tickable"

A module which implements this interface can be called every frame with the current application state. Tickable modules represent the brain of this application.

### Interface "Utility"

Utility modules aren't automatically called but can be called by other modules. They represent common functions offered by plugins.

## Shared

The shared package contains the shared manager which repesents the application state. It contains data values and all existing modules. Every frame the modules receive the current state. While it may be tempting to store the shared manager inside the module you must never do this. It will probably work but there is no guarantee that a single instance of this manager may become invalid. 

## Test

The (unit) test package of the kernel. 