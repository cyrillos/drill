class Solution:
    def isHappy(self, n: int) -> bool:
        cache = set()

        def make_squared_sum(n):
            s = 0
            while n:
                a = n % 10
                s += a * a
                n //= 10
            return s

        while True:
            v = make_squared_sum(n)
            if v == 1:
                return True
            # The trick is to detect cycles
            if v in cache:
                break
            cache.add(v)
            n = v

        return False

data = [
    19,
    2,
]
for i in range(0, len(data)):
    print(Solution().isHappy(data[i]))
