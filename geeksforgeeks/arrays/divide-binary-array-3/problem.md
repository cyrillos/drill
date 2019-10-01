[Divide binary array into three equal parts with same value](https://www.geeksforgeeks.org/divide-binary-array-into-three-equal-parts-with-same-value/)
============================================================

Given an array A of length n such that it contains only `0`s and `1`s.

The task is to divide the array into _THREE_ different non-empty parts
such that all of these parts represent the same binary value (in decimals).

If it is possible, return any `[i, j]` with `i+1` < `j`, such that:
1. A[0], A[1], …, A[i] is the first part.
2. A[i+1], A[i+2], …, A[j-1] is the second part.
3. A[j], A[j+1], …, A[n-1] is the third part.

Note: All three parts should have equal binary value.
However, If it is not possible, return `[-1, -1]`.

Examples:
```
Input : A = [1, 1, 1, 1, 1, 1]
Output : [1, 4]
```

All three parts are,

A[0] to A[1] first part,
A[2] to A[3] second part,
A[4] to A[5] third part.

```
Input: A = [1,0,1,0,1]
Output: [0,3]

Input : A = [1, 0, 0, 1, 0, 1]
Output : [0, 4]
```
