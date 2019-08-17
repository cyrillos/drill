[isomorphic string conversion](https://leetcode.com/discuss/interview-question/340493/google-onsite-isomorphic-string-conversion)
------------------------------

Given 2 strings s and t, determine if you can convert s into t.
The rule of conversion is once you changed a letter you have
to change **all occurrences** of that letter.

Example 1:
```
Input: s = "abca", t = "dced"
Output: true
```
Explanation: abca ('a' to 'd') -> dbcd ('c' to 'e') -> dbed ('b' to 'c') -> dced

Example 2:
```
Input: s = "ab", t = "ba"
Output: true
```
Explanation: ab -> ac -> bc -> ba

Example 3:
```
Input: s = "abcdefghijklmnopqrstuvwxyz", t = "bcdefghijklmnopqrstuvwxyza"
Output: true
```
Both strings contain only lowercase English letters.
