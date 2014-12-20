# A* Benchmark

Benchmark can be enabled by using `DEFINES+=A_STAR_BENCHMARK` in the additional arguments of qmake for the plugins VanillaModel and VanillaDemo.

Benchmarks were executed in Debug mode.

## Default implementation
    
    findNeighborsTime = 32841ms, loopTime = 45844ms, teleportTime = 5198ms, totalTime = 46819ms, walkTime = 6267ms
    findNeighborsTime = 33041ms, loopTime = 45887ms, teleportTime = 5091ms, totalTime = 46822ms, walkTime = 6363ms
    findNeighborsTime = 32586ms, loopTime = 45382ms, teleportTime = 4944ms, totalTime = 46317ms, walkTime = 6365ms
    
## Default implementation with old blocking loop (outer loop over blockedByBlocks)

    findNeighborsTime = 33499ms, loopTime = 46369ms, teleportTime = 4970ms, totalTime = 47333ms, walkTime = 6466ms
    findNeighborsTime = 33767ms, loopTime = 46720ms, teleportTime = 5020ms, totalTime = 47671ms, walkTime = 6507ms
    findNeighborsTime = 33695ms, loopTime = 46692ms, teleportTime = 5187ms, totalTime = 47645ms, walkTime = 6349ms
    
Maybe a bit slower. Close enough for me to use new blocking loop.
    
## Default implementation with copy not blocking positions in getFreeNeighbor() instead of erasing

    findNeighborsTime = 32894ms, loopTime = 45647ms, teleportTime = 4936ms, totalTime = 46536ms, walkTime = 6429ms
    findNeighborsTime = 32839ms, loopTime = 45634ms, teleportTime = 5020ms, totalTime = 46560ms, walkTime = 6305ms
    findNeighborsTime = 33045ms, loopTime = 45761ms, teleportTime = 4860ms, totalTime = 46700ms, walkTime = 6451ms
    
No difference. At least i didn't make a mistake here.
    
## Default implementation with isBlocking() always false (fake implementation without the possible heavy comparison)

    findNeighborsTime = 21102ms, loopTime = 38170ms, teleportTime = 5514ms, totalTime = 39620ms, walkTime = 10257ms
    findNeighborsTime = 21659ms, loopTime = 38733ms, teleportTime = 5621ms, totalTime = 40152ms, walkTime = 10154ms
    findNeighborsTime = 21178ms, loopTime = 37961ms, teleportTime = 5414ms, totalTime = 39422ms, walkTime = 10056ms
    
11000ms. I want that :(
    
## Default implementation with FRTS_FAST_ID

    findNeighborsTime = 31770ms, loopTime = 44515ms, teleportTime = 4968ms, totalTime = 45473ms, walkTime = 6406ms
    findNeighborsTime = 31797ms, loopTime = 44556ms, teleportTime = 5078ms, totalTime = 45467ms, walkTime = 6221ms
    findNeighborsTime = 31989ms, loopTime = 44619ms, teleportTime = 5087ms, totalTime = 45539ms, walkTime = 6145ms
    
findNeighborsTime is approx. 1000ms faster. Not much but enough to think about a faster point implementation. Let's do it.
    
### Second run with unordered_map instead of map in id implementation
    
    findNeighborsTime = 30784ms, loopTime = 43493ms, teleportTime = 5003ms, totalTime = 44751ms, walkTime = 6368ms
    findNeighborsTime = 30802ms, loopTime = 43528ms, teleportTime = 4892ms, totalTime = 44846ms, walkTime = 6488ms
    findNeighborsTime = 31048ms, loopTime = 43573ms, teleportTime = 4876ms, totalTime = 44814ms, walkTime = 6335ms
    
Roughly another 1000ms faster.

## Default implementation with FRTS_FAST_ID and path calculation from goal to start (no reverse)

    findNeighborsTime = 29884ms, loopTime = 42103ms, teleportTime = 4610ms, totalTime = 43351ms, walkTime = 6200ms
    findNeighborsTime = 30020ms, loopTime = 42158ms, teleportTime = 4692ms, totalTime = 43372ms, walkTime = 6067ms
    findNeighborsTime = 29849ms, loopTime = 42155ms, teleportTime = 4717ms, totalTime = 43366ms, walkTime = 6223ms
    
Not sure why findNeighborsTime is faster. Probably only an artifact of this benchmark. Reverse seems not to use much cpu time. Maybe for veeeeeeery long path but even then A* itself will be much more serious. So this is not necessary and it makes the hole thing more complicated.

After lots of experiments it is clear that calculating a unique key from x, y and z is way more expensive (tested to string, pairing functions...) than creating a point directly.