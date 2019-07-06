import sys

class Solution:
    def thirdMax(self, a: [int]) -> int:
        min_value = -sys.maxsize - 1
        q = [min_value] * 4

        def save_value(v):
            for i in range(0, len(q)):
                if q[i] == v:
                    return
            q[0] = v
            q.sort()
            q[0] = min_value

        for i in range(0, len(a)):
            save_value(a[i])

        if q[-3] == min_value:
            return q[-1]

        return q[-3]

data = [
    [1,1,2],        # -> 2
    [1,2,3,4,5],    # -> 3
    [3, 2, 1],      # -> 1
    [1, 2],         # -> 2
    [2, 2, 3, 1],   # -> 1
]

for i in range(0, len(data)):
    print(Solution().thirdMax(data[i]))
