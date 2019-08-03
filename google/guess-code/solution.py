class Solution:
    def GuessCode(self, pin: str, guess: str) -> str:
        res = []
        d = {}
        for i in range(0, len(pin)):
            d[pin[i]] = d[pin[i]]+1 if pin[i] in d else 1
        for i in range(0, len(pin)):
            if pin[i] == guess[i]:
                res.append("*")
                d[guess[i]] -= 1
            elif guess[i] in d:
                if d[guess[i]] > 0:
                    res.append("o")
                    d[guess[i]] -= 1
                else:
                    res.append("_")
            else:
                res.append("_")
        return "".join(res)

data = [
    ["1432", "1246", "*oo_"],   # => "*oo_"
    ["1234", "1234", "****"],   # => "****"
    ["1234", "5678", "____"],   # => "____"
    ["1224", "5242", "_*oo"],   # => "_*oo"
    ["1234", "1224", "**_*"],   # => "**_*"
    ["2124", "1224", "oo**"],   # => "oo**"
]
for i in range(0, len(data)):
    ret = Solution().GuessCode(data[i][0], data[i][1])
    print(data[i][0], data[i][1], ret, ret == data[i][2])
