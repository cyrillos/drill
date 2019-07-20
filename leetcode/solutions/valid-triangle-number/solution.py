from bisect import bisect_left

class Solution:
    def triangleNumber(self, a):
        a.sort()
        acc = 0
        #
        # The key moment is triangle inequasion:
        # every two sides sum should be greater than
        # third side: so just sort edges and find third
        # side from the rest.
        for i in range(0, len(a)):
            for j in range(i+1, len(a)):
                # choose i, j and find thidr side
                # starting from j + 1.
                idx = bisect_left(a, a[i] + a[j], j+1)
                acc += idx - 1 - j
        return acc

data = [
    [2,2,3,4],          # => 3 (2,3,4 | 2,3,4 | 2,2,3)
]

for i in range(0, len(data)):
    print(Solution().triangleNumber(data[i]))
