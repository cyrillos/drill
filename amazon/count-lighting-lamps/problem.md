Counting lighting lamps
-----------------------

You are given the `1-N` lamps. A lamp is lighting if only her trigger is on and
all previous lamps are on. You are provided with array `A` where each of it
carries the moment when the lamp is turning on. Find out the number of moments
when all lamps with trigger on were firing.

Example 1
```
Input: [1,2,3,4,5]
Output: [1,2,3,4,5]
```
Explanation: Each lamp has been turned on after another so on each moment
we have lamps with trigger on and firing.

Example 2
```
Input: [5,4,3,2,1]
Output: [1]
```
Explanation: The lamps are turning on in backward order so only at last
moment the lamps which are switched on are lighting.

Example 3
```
Input: [2,1,3]
Output: [2,3]
```
Explanation: At moment 2 lamps 2 and 1 are on, at moment 3 all lamps are on.
