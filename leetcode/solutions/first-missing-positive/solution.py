class Solution:
    def firstMissingPositive(self, a):
        if len(a) < 1:
            return 1

        #
        # Remap values to indices (similar trick
        # is used for sorting by counting), but
        # that value 1 would have index 0, iow
        # [4,3,2,1] => [1,2,3,4]
        #
        # Note that we can't use for() cycle here,
        # otherwise we might miss to swap, say
        # [3,4,2,1] => [2,4,3,1] => [2,1,3,4]
        i = 0
        while i < len(a):
            if a[i] > 0 and a[i] <= len(a) and a[a[i]-1] != a[i]:
                a[a[i]-1],a[i] = a[i],a[a[i]-1]
            else:
                i += 1

        #
        # We expect first positive integer (which is 1)
        # to be at 0 index and sequence get increased.
        for i in range(0, len(a)):
            if(a[i] != i + 1):
                return i + 1
        return len(a)+1

#data = [
#    [3,4,2,1],          # -> 5
#    [-10, -7, -6, -4, -1,
#     0, 0, 1, 2, 2, 4, 6,
#     8, 10, 11, 11],    # -> 3
#    [0,1,2],            # -> 3
#    [1,2,0],            # -> 3
#    [3,4,-1,1],         # -> 2
#    [7,8,9,11,12],      # -> 1
#    [-1,4,2,1,9,10],    # -> 3
#    [],                 # -> 1
#    [4,1,2,3],          # -> 5
#    [3,4,-1,1]          # -> 2
#]
#
#for i in range(0, len(data)):
#    print(Solution().firstMissingPositive(data[i]))
