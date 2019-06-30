class Solution:
    #
    # DP: Fill up two arrays with max heights,
    # then walk over each positions and calc
    # how much height left (ie horizontal bar
    # between min[left;right]) to fill with
    # water.
    def trap_two_arrays(self, a):
        if not a or len(a) < 3:
            return 0

        accum = 0
        left = [0] * len(a)
        right = [0] * len(a)

        left[0] = a[0]
        for i in range(1, len(a)):
            left[i] = max(left[i-1], a[i])

        right[-1] = a[-1]
        for i in range(len(a)-2, -1, -1):
            right[i] = max(right[i+1], a[i])

        for i in range(0, len(a)):
            accum += min(left[i], right[i]) - a[i]

        return accum

    def trap(self, a):
        return self.trap_two_arrays(a)

data = [
    [4,0,2,0,5,0,2,0,1],
]

for a in data:
    print(Solution().trap(a))
