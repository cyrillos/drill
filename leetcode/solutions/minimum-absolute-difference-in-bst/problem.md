[530. Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/)
=========================================

Given the `root` of a Binary Search Tree (BST), return the minimum absolute
difference between the values of any two different nodes in the tree.

Example 1:
```
      4
     / \
    2   6
   / \
  1   3

Input: root = [4,2,6,1,3]
Output: 1
```

Example 2:
```
    1
   / \
  0  48
    /  \
   12  49

Input: root = [1,0,48,null,null,12,49]
Output: 1
```

Constraints:

 - The number of nodes in the tree is in the range `[2, 10^4]`.
 - `0 <= Node.val <= 10^5`
