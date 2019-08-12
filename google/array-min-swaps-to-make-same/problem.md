[min swaps for all elements to be the same](https://leetcode.com/discuss/interview-question/356507/google-oa-2019-min-swaps-for-all-elements-to-be-the-same)
===========================================

Given 2 arrays `a` and `b`, each containing `n` integers.
You can swap elements at the same index. Return the minimum number of
swaps needed for all elements in either `a` or `b` to be the same
or `-1` if that is not possible.

Example 1:
````
Input:
a = [1, 2, 3, 6, 3, 2]
b = [2, 1, 2, 2, 2, 4]

Output: 2

Explanation:
You can swap elements at index 1 and 5, so that all elements in b will be equal to 2.
a = [1, 1, 3, 6, 3, 4]
b = [2, 2, 2, 2, 2, 2]
```

Example 2:
```
Input:
a = [1, 2, 1, 2]
b = [2, 6, 1, 2]

Output: -1
```

Constraints:
------------
 - `n` is an integer within the range `[1..100,000]`;
 - each element of arrays `a` and `b` is an integer within the range `[1..6]`.
