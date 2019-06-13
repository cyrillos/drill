class Solution:
    def multiply(self, a: str, b: str) -> str:
        acc = [0] * (len(a) + len(b))

        carry = 0
        pos, off = 0, 0
        for i in range(len(a)-1, -1, -1):
            pos = off
            for j in range(len(b)-1, -1, -1):
                k = acc[pos] + int(a[i]) * int(b[j]) + carry
                carry = k // 10
                k = k - carry * 10
                acc[pos], pos = k, pos+1
            else:
                acc[pos], carry = carry, 0
                off += 1

        res = "".join(map(lambda x: str(x), acc[::-1]))
        for i in range(0, len(res)):
            if res[i] != '0':
                return res[i:]
        return "0"

data = [
    ["123", "456"],
    ["12", "98"],
    ["99", "99"],
    ["98", "9"],
    ["1", "2"],
    ["6", "4"],
]

for i in range(0, len(data)):
    print(Solution().multiply(data[i][0], data[i][1]))
