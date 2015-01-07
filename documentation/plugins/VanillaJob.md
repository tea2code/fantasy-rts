# Vanilla Job

This plugin manages new jobs and executes them if an adequate entity is provided. An adequate entity is defined as one which has the **Curriculum** and all the required ids are matched by the entity.

## Installation

Default path of plugin is `vanilla-job/vanilla-job`.

## Development

Access to all necessary interfaces can be aquired by adding the source directory to the include pathes and include `frts/vanillajob` (e.g. `#include <frts/vanillajob>`).

## Interfaces

### Job

The job interface must be implemented by any class which wants to behave as a job. All methods are executed by the job handler or job manager and shouldn't be called manually. The method `stop()` is called if the job should be stopped. The methods `execute()` and `stop()` are called every frame until they return `Finished`, `Stop` or `Cancel`. The state `Stop` means that the job handler will switch from calling `execute()` to calling `stop()` while the state `Cancel` means that the job will be scheduled for later execution by another entity.

### Job Handler

The job handler is implemented as a tickable module. It will execute the currently running jobs every frame until finished.

Load using `frts/JobHandler` in the `updateModules` section of the load file. 

Will identify itself by the name and type `frts::JobHandler`.

#### Events

The job handler will raise the following events. They both contain a single entity value with id `frts.vanillajob.event.value.entity`. The ids can also be found in the static class `JobIds`. 

- **Canceled:** Send if a job has been canceled and will be executed later. Use event id `frts.vanillajob.event.job.canceled`.
- **Finished:** Send if a job has been finished. Use event id `frts.vanillajob.event.job.finished`.
- **Stopped:** Send if a job has been stopped. Use event id `frts.vanillajob.event.job.stopped`.

### Job Manager

The job manager is implemented as an utility module. It has methods to add new jobs, start them by using an entity with curriculum component and stop jobs.

Load using `frts/JobManager` in the `utilities` section of the load file. 

Will identify itself by the name and type `frts::JobManager`. It can also be found in the static class `JobIds`. 