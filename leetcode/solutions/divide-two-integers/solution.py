class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        sign = -1 if ((dividend < 0) ^ (divisor < 0)) else 1
        a = abs(dividend)
        b = abs(divisor)

        #
        # Can we represent @a as @b * 2^n polynomial?
        # IOW, @a = b * 2^(n) + b * 2^(n-1) ...
        # then simply count terms, ie 2^(n) members.
        #
        # The order is important: we start from top
        # power and go downward since we need to find
        # max multiplicator of divisor.
        #
        # For example a = 10 and b = 3:
        #  10 = 3*2 + 3*1 = 6 + 3 = 9 => 3*2^1 + 3*2^0
        #
        accum, terms = 0, 0
        for i in range(31, -1, -1):
            v = b << i
            if accum + v <= a:
                accum += v
                terms |= 1 << i

        if sign < 0 and terms >= 2147483648:
            terms = 2147483648
        elif terms >= 2147483647:
            terms = 2147483647
        return sign * terms

data = [
    [10, 3],            # =>  3
    [7, -3],            # => -2
]
for i in range(0, len(data)):
    print(Solution().divide(data[i][0], data[i][1]))
