# Tasks

A task is a job executed by the ai directory to simulate certain actions. The execution of tasks is controlled by the decision tree.

## Pipeline

Pipelines are a sub tree in the decision tree consisting of a pipeline start and stop and a arbitrary number of tasks in between. These tasks can access values in the pipeline using the *in* and *out* attributes. What values a task can read and write are defined below.

For example harvesting berries could consists of the following pipeline (example simplified):

    Find berry shrub -[Position]-> Go to berry shrub -[]-> Collect berries

This example consists of three seperate tasks while two of them share a value the position of a found berry shrub.

## Task Types

The following is a description of all supported task types and their parameters.

### Random Point:

This task finds a random free point in the region for the current entity. It will be removed when no longer needed.

**ID:** ai.task.type.demo.randompoint   
**Parameter:** -   
**Result:** Requires that an *out* attribute is set. Will write the found point to it.

### Drop:

Places a entity "stored" in the pipeline at the current position.

**ID:** ai.task.type.drop  
**Parameter:** Requires that an *in* attribute is set. Considers the value as an entity.   
**Result:** -    

### Find Resource:

Finds a entity containing the specified resource type. This will lock the resource for other entities. You can release a locked resource using the "Release Resource" task.

**ID:** ai.task.type.find.resource  
**Parameter:** Requires that a resource type is specified in the *resource* attribute or as a value in the *in* attribute.   
**Result:** Requires than an *out* attribute is set. Will write the found entity to it.    

### Find Entity:

Finds the position of a entity.

**ID:** ai.task.type.find.entity  
**Parameter:** Requires that an *in* attribute is set. Considers the value as an entity.   
**Result:** Requires than an *out* attribute is set. Will write the position of the given entity to it.    

### Go To:

Finds a path to the goal and moves the entity there.

**ID:** ai.task.type.goto  
**Parameter:** Requires that an *in* attribute is set. Considers the value as an point.        
**Result:** -     

### Harvest:

"Harvests" a entity collecting the resource 

**ID:** ai.task.type.harvest  
**Parameter:** Requires that an *in* attribute is set. Considers the value as an entity.   
**Result:** Requires than an *out* attribute is set. Will write the resource entity to it.    

### Idle:

Let's the entity do nothing.

**ID:** ai.task.type.idle  
**Parameter:** Requires that a duration is specified in the *duration* attribute or as a value in the *in* attribute.  
**Result:** -    

### Set Pipeline Value:

Set a value in the pipeline. Can also be used to store a value in another pipeline variable.

**ID:** ai.task.type.pipeline.value  
**Parameter:** Requires that a value is specified in the *value* attribute or as a value in the *in* attribute.   
**Result:** Requires than an *out* attribute is set. Will write the value to it.    

### Release Resource:

Will release a locked resource.

**ID:** ai.task.type.release.resource  
**Parameter:** Requires that an *in* attribute is set. Considers the value as an entity containing a resource.   
**Result:** -    
