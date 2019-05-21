class Solution:
    def reverse(self, x: int) -> int:
        # limits requested
        hi = 2147483647
        lo = 2147483648
        if x == 0: return 0
        if x < 0:
            x, sign = -x, -1
        else:
            sign = 1
        v = 0
        while x != 0:
            m = x // 10
            k = m * 10
            r = x - k
            v = (v * 10) + r
            x = m
        # Make sure we fit the limits
        if v > hi: return 0
        if sign < 0 and v > lo: return 0
        return sign*v

#data=[
#    1534236469, # => 0
#    1425,       # => 5241
#    123,        # => 321
#    -123,       # => -321
#    120         # => 21
#]
#for i in range(0, len(data)):
#    print(Solution().reverse(data[i]))
