class Solution:
    def trap(self, a):
        if not a or len(a) < 3:
            return 0
        hl = a[0]
        hr = a[-1]
        l, r = 1, len(a) - 2
        accum = 0
        while l <= r:
            if hl <= hr:
                if a[l] <= hl:
                    accum += hl - a[l]
                else:
                    hl = a[l]
                l += 1
            else:
                if a[r] <= hr:
                    accum += hr - a[r]
                else:
                    hr = a[r]
                r -= 1
        return accum
