class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        elif x < 10:
            return True

        r = 0
        n = x
        while n > 0:
            r = (r + n % 10) * 10
            n //= 10
        r //= 10

        return True if x == r else False

data = [
    50005,      #-> true
    100001,     #-> true
    1000021,    #-> false
    0,          #-> true
    55,         #-> true
    121,        #-> true
    20,         #-> false
    11,         #-> true
    5665,       #-> true
    565,        #-> true
    -121,       #-> false
    10,         #-> false
]
for i in range(0, len(data)):
    print(data[i], Solution().isPalindrome(data[i]))
