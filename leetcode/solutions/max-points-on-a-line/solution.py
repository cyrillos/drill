import math

class Solution:
    def maxPoints(self, a) -> int:
        if len(a) <= 2:
            return len(a)
        res = 0
        #
        # This is N^2 algo -- we take each point
        # and then walk over the rest of the point
        # and remember the tangent between point
        # a[i] and a[j] via dictionary. Note that
        # float points are not correct much due to
        # comp architecture, so we rather remember
        # the tangent as a raio pair. Which we reduce
        # by gcd. And remember thet tangent is odd
        # function, tg(-x) = -tg(x) so we use k1, k2
        # for x mapping.
        for i in range(0, len(a)):
            d, same, vert = {}, 0, 1
            for j in range(i + 1, len(a)):
                if a[i] == a[j]:
                    same += 1
                elif a[i][0] == a[j][0]:
                    vert += 1
                else:
                    dy = (a[i][1] - a[j][1])
                    dx = (a[i][0] - a[j][0])
                    c = math.gcd(dx, dy)
                    dx //= c
                    dy //= c
                    k1 = (dx, dy)
                    k2 = (-dx, -dy)
                    if k1 in d:
                        d[k1] += 1
                        res = max(res, d[k1])
                    elif k2 in d:
                        d[k2] += 1
                        res = max(res, d[k2])
                    else:
                        d[k1] = 2
                        res = max(res, d[k1])
            res = max(res, max(list(d.values()) + [0]) + same)
            res = max(res, vert + same)
        return res

data = [
    [[1,1],[1,1],[1,1]],                    # => 3
    [[0,0],[1,1],[1,-1]],                   # => 2
    [[1,1],[1,1],[2,2]],                    # => 3
    [[0,0],[0,0],[1,1]],                    # => 3
    [[2,2],[1,1],[3,3]],                    # => 3
    [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]],  # => 4
]

for i in range(0, len(data)):
    print(Solution().maxPoints(data[i]))
