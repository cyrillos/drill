class Solution:
    def sortedSquares(self, a):
        #
        # Plain sorting in place.
        # Another option is to note
        # that negative numbers are giving
        # squares in reverse order, iow
        # [-7,-3] => [49, 9], thus we could
        # allocate new array and merge negative
        # and positive squares into it (just
        # find last negative element and split
        # array into two, and them merge it via
        # two pointers).
        for i in range(0, len(a)):
            a[i] = a[i] * a[i]
        a.sort()
        return a

data = [
    [-4,-1,0,3,10],     # => [0,1,9,16,100]
    [-7,-3,2,3,11],     # => [4,9,9,49,121]
]
for i in range(0, len(data)):
    print(Solution().sortedSquares(data[i]))
