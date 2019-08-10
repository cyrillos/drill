def bsearch(a, v):
    lo, hi = 0, len(a)-1
    while lo <= hi:
        pos = (lo+hi)//2
        if a[pos] == v:
            # find leftmost index in
            # case of duplicates.
            while pos >= 0 and a[pos] == v:
                pos -= 1
            if pos < 0:
                return 0
            return pos if a[pos] == v else pos + 1
        elif a[pos] < v:
            lo = pos+1
        else:
            hi = pos-1
    return -1

class Solution:
    def ArraysInOrder(self, a, b):
        res = []
        a.sort()
        for i in range(0, len(b)):
            pos = bsearch(a, b[i])
            if pos < 0:
                continue
            while a[pos] == b[i]:
                res.append(b[i])
                pos += 1
                if pos >= len(a):
                    break
        return res

data = [
    [[1,2,3,4,5,6,6,4,3,2,1],
     [5,2,4,3,1]]
]
for i in range(0, len(data)):
    print(Solution().ArraysInOrder(data[i][0], data[i][1]))
