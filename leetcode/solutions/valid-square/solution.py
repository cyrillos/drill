class Solution:
    def validSquare(self, p1: [int], p2: [int], p3: [int], p4: [int]) -> bool:
        #
        # Sort them in x and y, to make walk order
        p = [p1,p2,p3,p4]
        p.sort(key=lambda x: (x[0], x[1]))

        #
        # Squared distance
        def dist(i, j):
            x = (p[i][0] - p[j][0])
            y = (p[i][1] - p[j][1])
            return x*x + y*y

        d01 = dist(0,1)
        d13 = dist(1,3)
        d32 = dist(3,2)
        d20 = dist(2,0)

        if d01 == 0 or d13 == 0 or d32 == 0 or d20 == 0:
            return False

        if dist(0,3) != dist(1,2): return False
        if d01 != d13: return False
        if d13 != d32: return False
        if d32 != d20: return False

        return True

data = [
    [[0, 0], [0, 1], [1, 0], [1, 1]],       # => True
]
for i in range(0, len(data)):
    print(Solution().validSquare(data[i][0], data[i][1], data[i][2], data[i][3]))
