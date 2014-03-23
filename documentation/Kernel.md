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

The log package contains implementations of loggers. Currently Easylogging++ is used. The log objects has a simple interface to create a log message. It can be accessed through the shared manager. A log message consists of a (hopefully) unique name for the module (for example the plugin module name) and the message. The configuration and the output files are stored in the directory log. Example:

    log->debug("Kernel", "Hello World");

This would output a message similar to

    23/03/2014 11:05:45,279295 - DEBUG - Kernel - Hello World

The supported log levels are in order of their verbosity:

- **Debug:** Use only for development related messages. Normally disabled in release builds.
- **Info:** Standard level for non critical messages. Normally disabled in major stable builds.
- **Warning:** Use for important messages which aren't critical as errors. Always active.
- **Error:** Use for exception and error messages. Always active.

## Test

The (unit) test package of the kernel. 