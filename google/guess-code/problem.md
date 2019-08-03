[Guess Pin Code](https://leetcode.com/discuss/interview-question/349416/goolge-onsite-guess-pin-code)
================

Given 2 strings pin and guess. Write a function to provide a hint
that indicates how digits in guess match the pin. Use:

- `*` - to indicate a number in the correct possition.
- `o` - to indicate that a number is present in the pin code but in a different possition.
- `_` - to indicate that there's no such number in the pin code.

Example 1:
```
Input: pin = "1432", guess = "1246"
Output: "*oo_"
```

Explanation:
1 is in the correct position so `*`
2 and 4 are present in the pin code but in different positions thus `oo`
There's no 6 in the pin code thus `_`

Example 2:
```
Input: pin = "1234", guess = "1234"
Output: "****"
```

Example 3:
```
Input: pin = "1234", guess = "5678"
Output: "____"
```

Example 4:
```
Input: pin = "1224", guess = "5242"
Output: "_*oo"
```

Example 5:
```
Input: pin = "1234", guess = "1224"
Output: "**_*"
```

Example 6:
```
Input: pin = "2124", guess = "1224"
Output: "oo**"
```

Constraints:
------------
 - pin.length == input.length
 - The input strings contain only digits `0-9`.
