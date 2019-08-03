class Solution:
    def isPalindrome(self, s: str) -> bool:
        i = 0
        j = len(s)-1
        while i < j:
            if s[i].isalnum() and s[j].isalnum():
                if s[i].lower() != s[j].lower():
                    return False
                i, j = i+1, j-1
            else:
                i = i + 0 if s[i].isalnum() else i + 1
                j = j - 0 if s[j].isalnum() else j - 1
        return True

data = [
    "A man, a plan, a canal: Panama",       # => true
    "race a car",                           # => false
]
for i in range(0, len(data)):
    print(Solution().isPalindrome(data[i]))
