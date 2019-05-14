class Solution:
    def findMedianSortedArrays(self, a: [int], b: [int]) -> float:
        len_a = len(a)
        len_b = len(b)
        len_c = len_a + len_b

        if len_c == 0:
            return -1

        #
        # Merge sorted arrays and consider two cases:
        # even number of elems
        #   take two in a middle and get an average value
        # odd number of elems
        #   take middle element

        c = [0] * len_c
        k = pos_a = pos_b = 0
        for k in range(0, len_c):
            if pos_a >= len_a:
                c[k], pos_b = b[pos_b], pos_b+1
            elif pos_b >= len_b:
                c[k], pos_a = a[pos_a], pos_a+1
            else:
                if a[pos_a] <= b[pos_b]:
                    c[k], pos_a = a[pos_a], pos_a+1
                else:
                    c[k], pos_b = b[pos_b], pos_b+1

        m = len_c % 2
        if m == 1:
            pos = (len_c - 1) // 2
            return c[pos]
        else:
            pos = len_c // 2
            return (c[pos-1] + c[pos]) / 2.

        return -1
#
#data = [
#    [[1,3],[2]],    # -> 2.0
#    [[1,2],[3,4]]   # -> (2 + 3) / 2 = 2.5
#]
#
#for i in range(0, len(data)):
#    print(Solution().findMedianSortedArrays(data[i][0], data[i][1]))
