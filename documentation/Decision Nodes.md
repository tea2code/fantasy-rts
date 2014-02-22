# Decision Nodes

Main part of the AI in this game is realized by a [decision tree](https://en.wikipedia.org/wiki/Decision_tree) for every dynamic entity.

## Visualization

To better validate decision trees they are drawn on every start. You can find them in the directory "log/decision/".

## Node Types

### Pipeline Start:

Initializes a new task pipeline.

**ID**: ai.decision.node.pipeline.start   
**Parameter:** -   

### Pipeline Stop:

Destroys and by this ends the current task pipeline.

**ID**: ai.decision.node.pipeline.stop   
**Parameter:** -   

### Random:

Chooses the next node by chance.

**ID**: ai.decision.node.random   
**Parameter:** See below.    

    random:
      - chance: <float, "The chance that this branch is choosen.">
        next: <id, "The id of the node executed if this branch is choosen.">

### Task:

Executes a task.

**ID**: ai.decision.node.task   
**Parameter:** See below.   

    task: <id, "The id of the task to execute.">