class Solution:
    def intToRoman(self, num: int) -> str:
        m = {
            1: 'I',
            4: 'IV',
            5: 'V',
            9: 'IX',
            10: 'X',
            40: 'XL',
            50: 'L',
            90: 'XC',
            100: 'C',
            400: 'CD',
            500: 'D',
            900: 'CM',
            1000: 'M',
        }

        res = []

        #
        # Opencoed for speed sake
        def decomposite(num, res):
            if num >= 1000:
                v = num // 1000
                num -= v * 1000
                res.extend([m[1000] * v])
                return num
            elif num >= 900:
                num -= 900
                res.extend(m[900])
                return num
            elif num >= 500:
                num -= 500
                res.extend(m[500])
                return num
            elif num >= 400:
                num -= 400
                res.extend(m[400])
                return num
            elif num >= 100:
                num -= 100
                res.extend(m[100])
                return num
            elif num >= 90:
                num -= 90
                res.extend(m[90])
                return num
            elif num >= 50:
                num -= 50
                res.extend(m[50])
                return num
            elif num >= 40:
                num -= 40
                res.extend(m[40])
                return num
            elif num >= 10:
                num -= 10
                res.extend(m[10])
                return num
            elif num >= 9:
                num -= 9
                res.extend(m[9])
                return num
            elif num >= 5:
                num -= 5
                res.extend(m[5])
                return num
            elif num >= 4:
                num -= 4
                res.extend(m[4])
                return num
            else:
                num -= 1
                res.extend(m[1])
                return num

        while num > 0:
            num = decomposite(num, res)
        return "".join(res)

data = [
    3000,       # -> MMM
    3900,       # -> MMMCM
    3,          # -> III
    4,          # -> IV
    9,          # -> IX
    58,         # -> LVIII
    1994,       # -> MCMXCIV
]
for i in range(0, len(data)):
    print(Solution().intToRoman(data[i]))
