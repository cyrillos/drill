import random

class Solution:
    def via_hash(self, a) -> int:
        d = { }
        n, idx = 0, 0
        for i in range(0, len(a)):
            d[a[i]] = d[a[i]] + 1 if a[i] in d else 1
            if n < d[a[i]]:
                n, idx = d[a[i]], a[i]
        return idx

    def via_sort(self, a) -> int:
        # because it must be there due to
        # definition of a major element, which
        # appears more than n/2 times.
        a.sort()
        return a[len(a)//2]

    def via_random(self, a) -> int:
        n = len(a) // 2
        while True:
            v = random.choice(a)
            if sum(1 for e in a if e == v) > n:
                return v

    def via_boyer_moore_voting(self, a) -> int:
        c = None
        n = 0
        for i in range(0, len(a)):
            if n == 0:
                c = a[i]
            n += (1 if a[i] == c else -1)
        return c

    #
    # I did hash initially, didn't considered
    # boyer-moore and random algos.
    def majorityElement(self, a) -> int:
        return self.via_boyer_moore_voting(a)

data = [
    [3,2,3],                # => 3
    [2,2,1,1,1,2,2],        # => 2
]
for i in range(0, len(data)):
    print(Solution().majorityElement(data[i]))
