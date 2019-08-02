class Solution:
    def merge(self, a, m, b, n) -> None:
        #
        # Here is a trick: sort from end
        # of arrays (ie m-1,n-1), pasting
        # to the last position of @a where
        # we have free space. IOW
        #
        #            v = (m-1)+(n-1)+1
        # [1,2,3,0,0,0], 3
        #      ^ = m-1
        #
        # [2,5,6], 3
        #      ^ = n-1
        #
        m, n = m-1, n-1
        while n >= 0:
            if m >=0 and a[m] > b[n]:
                a[m+n+1] = a[m]
                m -= 1
            else:
                a[m+n+1] = b[n]
                n -= 1

data = [
    [[1,2,3,0,0,0], 3, [2,5,6], 3],
    [[4,5,6,0,0,0], 3, [1,2,3], 3],
]
for i in range(0, len(data)):
    print(Solution().merge(data[i][0], data[i][1], data[i][2], data[i][3]))
