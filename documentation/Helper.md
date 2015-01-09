# Helper

In directory *src-helper* are a couple of helper functions, utility classes...

## file.h

File related helper functions. Currently only a file exists method.

## random.h

Currently implements functions to randomly select an element from a given range and generate random integers and floats.

## RecursiveLock.h

If `SPIN_LOCK` is defined this implements a spin lock based, recursive mutex. If not it will use the STL recursive mutex. 

## timer.h

Simple function to get the current time since the begin of the epoch in high resolution. Based on this function there is also a performance logger implemented which allows to log the duration time of a scope (function...).

## Base Implementations

Contains base implementations of data values and modules:

- BaseDataValue.h
- BaseTickable.h
- BaseUtility.h