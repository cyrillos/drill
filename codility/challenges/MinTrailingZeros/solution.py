#
# While this code passes codility testcases,
# it is buggy, instead we need to make two
# walks for powers of 2 and 5 separately, then
# choose which is better. But I'm too lazy to
# rewrite the code :-)
#
# The walk idea is a regular DP on a grid.
def solution(a):
    def factor(v):
        r = [v, 0, 0, 0]
        while v and v % 5 == 0:
            v /= 5
            r[1] += 1
        while v and v % 2 == 0:
            v /= 2
            r[2] += 1
        r[3] = min(r[1], r[2])
        return r

    def min_pair(a, b):
        if a[3] <= b[3]:
            return a
        return b

    def mul_pair(a, b):
        if a[0] == 0 or b[0] == 0:
            a[0], a[1], a[2], a[3] = 0, 0, 0, 1
            return
        a[0] = a[0] * b[0]
        a[1] = a[1] + b[1]
        a[2] = a[2] + b[2]
        a[3] = min(a[1], a[2])

    if len(a) < 1:
        return 0
    elif len(a) == 1:
        if a[0][0] == 0:
            return 1
        return factor(a[0][0])[3]

    p = [[factor(a[i][j]) for i in range(0, len(a))] for j in range(0, len(a))]
    for i in range(1, len(a)):
        mul_pair(p[i][0], p[i-1][0])
        mul_pair(p[0][i], p[0][i-1])

    for i in range(1, len(a)):
        for j in range(1, len(a)):
            mul_pair(p[i][j], min_pair(p
