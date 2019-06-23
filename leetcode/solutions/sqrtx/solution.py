class Solution:
    def mySqrt(self, x: int) -> int:
        if x <= 1: return x

        #
        # Use a simple approach as task implies: just
        # binary search in range [1, x]. Note that we're
        # using strict less comparision here on purpose
        # to find first "bigger" value, same applies to
        # hight bound, then simply return first "less" value.
        lo, hi = 1, x
        while lo < hi:
            m = (lo+hi)//2
            v = x // m
            if v == m:
                return m
            elif v < m:
                hi = m
            else:
                lo = m + 1
        return lo-1

data = [i for i in range(0, 26)]
for i in data:
    print(i, '=>', Solution().mySqrt(i))
