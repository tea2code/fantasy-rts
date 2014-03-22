# Execution Phases

Execution of this application is separated in a couple distinct phases which normally end in the game loop after a number of initialization phases.

## Phases

The following describes all phases and possible plugin or module api calls.

### 1. Read Load File

The application core parses the load file which defines all plugins to load, the modules to start and the configuration files to read.