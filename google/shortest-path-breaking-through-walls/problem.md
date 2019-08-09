[Shortest Path Breaking Through Walls](https://leetcode.com/discuss/interview-question/353827/google-onsite-shortest-path-breaking-through-walls)
======================================

Given a 2D grid of size r * c. 0 is walkable, and 1 is a wall. You can move up, down,
left or right at a time. Now you are allowed to break at most 1 wall, what is the minimum
steps to walk from the upper left corner (0, 0) to the lower right corner (r-1, c-1)?

Example 1:
```
Input:
[[0, 1, 0, 0, 0],
 [0, 0, 0, 1, 0],
 [1, 1, 0, 1, 0],
 [1, 1, 1, 1, 0]]

Output: 7
```

Explanation: Change `1` at (0, 1) to `0`, the shortest path is as follows:
(0, 0) -> (0, 1) -> (0, 2) -> (0, 3) -> (0, 4) -> (1, 4) -> (2, 4) -> (3, 4)
There are other options of length 7, not listed here.

Example 2:
```
Input:
[[0, 1, 1],
 [1, 1, 0],
 [1, 1, 0]]

Output: -1
```

Explanation: Regardless of which `1` is changed to `0`, there is no viable path.
Follow-up:
What if you can break k walls?

Example 1:
```
Input: k = 2
[[0, 1, 0, 0, 0],
 [0, 0, 0, 1, 0],
 [0, 1, 1, 1, 1],
 [0, 1, 1, 1, 1],
 [1, 1, 1, 1, 0]]

Output: 10
```

Explanation: Change (2, 4) and (3, 4) to `0`.
Route (0, 0) -> (1, 0) -> (1, 1) -> (1, 2) -> (0, 2) -> (0, 3) -> (0, 4) -> (1, 4) -> (2, 4) -> (3, 4) -> (4, 4)

Hint:
-----
https://medium.com/@jeantimex/3-dimensional-breadth-first-search-62a54596f74a
