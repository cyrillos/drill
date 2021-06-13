[79. Word Search](https://leetcode.com/problems/word-search/)
=================

Given an `m x n` gird of characters `board` and a string `word`,
return `true` if `word` exists in the grid.

The word can be constructed from letters of sequentially adjacent
cells, where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once.

**Note:** There will be some test cases with a `board` or a `word`
larger than constraints to test if your solution is using pruning.

Example 1:
![image](word2.jpg)
```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
```

Example 2:
![image](word-1.jpg)
```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
```

Example 3:
![image](word3.jpg)
```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
```

Constraints:
------------
 - m == board.length
 - n = board[i].length
 - 1 <= m, n <= 6
 - 1 <= word.length <= 15
 - board and word consists of only lowercase and uppercase English letters.