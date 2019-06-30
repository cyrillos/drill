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

    #
    # DP: Move two pointers at left and right,
    # basically imagine you've a horizontal line
    # between them with hight of lowest bar inbetween,
    # then you simply accum the space left.
    def trap_two_pointers(self, a):
        if not a or len(a) < 3:
            return 0

        accum = 0
        left_max = a[0]
        right_max = a[-1]

        l, r = 0, len(a)-1
        while l < r:
            if a[l] < a[r]:
                if a[l] >= left_max:
                    left_max = a[l]
                else:
                    accum += left_max - a[l]
                l += 1
            else:
                if a[r] >= right_max:
                    right_max = a[r]
                else:
                    accum += right_max - a[r]
                r -= 1

        return accum

    def trap(self, a):
        return self.trap_two_arrays(a)

data = [
    [4,0,2,0,5,0,2,0,1],
]

for a in data:
    print(Solution().trap(a))
