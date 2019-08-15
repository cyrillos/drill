[Fix the parenthesis in the string](https://www.knowsh.com/Notes/250490/Fix-The-Parenthesis-In-The-String)
===================================

Fix the parenthesis in the string by deleting unmatched parenthesis.
Write a method to fix the given string by removing the unmatched parenthesis.

Example
```
Input string: (((()      Output string: ()
Input string: ))()       Output string: ()
Input string: )aabc(c)d  Output string: aabc(c)d
```

Note
----
String contains only '(', ')' and small alphabets.

Complexity
----------
 - Time complexity: O(n) where n is the length of the given string.
   We are traversing the string linear.
 - Space complexity: O(n) where n is the length of given string.
   That is the maximum size of any stack we are using to store the indexes.
