# Execution Phases

Execution of this application is separated in a couple distinct phases which normally end in the game loop after a number of initialization phases.

## Phases

The following describes all phases and possible plugin or module api calls.

### 1. Read Load File

The application core parses the load file which defines all plugins to load, the modules to start and the configuration files to read.

### 2. Load Libraries

The next step tries to load all shared libraries representing the plugins.

### 3. Get Modules

In the third phase the modules are created using the loaded modules. Failing to find a module is considered an error.

### 4. Check Required Modules

Every module has now the chance to check if any required module is missing by accessing the shared manager.

### 5. Preinitialize Modules.

A first initialization step which can be used to preconfigure modules. For example influence the creation of data. Should only be used for cases where no other phase is fitting. It is possible to request another execution if required. If too many extra executions are requested it is assumed that a dead lock has occurred and an exception is thrown.

### 6. Create Data

The modules should create any data objects in the shared manager in this phase. It is possible to request another execution if required. This allows for example to let another module create it's data objects and then modify them afterwards. If too many extra executions are requested it is assumed that a dead lock has occurred and an exception is thrown.

### 7. Check Required Data

Every module has now the chance to check if any required data object is missing by accessing the shared manager.

### 8. Register Main Config Keys

Modules must register main config keys in this step. This allows the application core to call for every config key the appropriate modules.

### 9. Read Config

The application core parse the config in this step and whenever if encounters a registered key it will call the modules registered for this key.

### 10. Validate Data

After reading all configuration files the modules can validate the data. This includes their own data but also data from other modules.

### 11. Initialize Modules

The application core will call the *init()* method in this phase. Every module can now initialize it's internal state and make last changes to the shared manager. It is possible to request another execution if required. If too many extra executions are requested it is assumed that a dead lock has occurred and an exception is thrown.

### 12. Startup

Before running the game a initial set of modules is executed. This allows for example to load a specific map. The frame data of the shared manager doesn't have any defined value and is most likely to be null.

### 13. Run Game

The most important phase. The application core will start the main loop which runs until the quit flag is set on the shared manager.

### 14. Shutdown

After stopping the main loop another set of modules is executed. This may involve cleanup modules and saving the current game. Like in phase **Startup** the frame data doesn't have any defined value and may or may not be null.

### 15. Application Finished

The end. Have a nice day. Roll credits.