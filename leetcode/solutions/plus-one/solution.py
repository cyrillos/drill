class Solution:
    def plusOne(self, digits):
        if len(digits) == 0:
            return []
        res = digits[:]
        print(res)
        carry = 0
        v = res[-1] + 1
        if v == 10:
            res[-1] = 0
            carry = 1
        else:
            res[-1] = v
            return res
        for i in range(len(res)-2, -1, -1):
            res[i] += carry
            if res[i] == 10:
                res[i] = 0
                carry = 1
            else:
                return res
        if carry:
            res.insert(0, 1)
        return res
#data=[
#    [1,2,3],
#    [1,2,9]
#]
#for i in range(0, len(data)):
#    print(Solution().plusOne(data[i]))
