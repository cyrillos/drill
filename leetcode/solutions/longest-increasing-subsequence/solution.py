import bisect

class Solution:
#    #
#    # O(n^2) DP algo: simply mark each element as having length 1 in d,
#    # then pick one "i" and assume that problem is solved for [0;i-1] case,
#    # thus simply walk all previous and find if we can append current element
#    # i into previous subsequences j = [0;i-1]. So the a[j] must be less then
#    # a[i] then we update current longest increasing subsequence at position i.
#    # Finally just find the max value from d array.
#    #
#    def lengthOfLIS(self, a):
#        d = [1] * len(a)
#        n = 0
#        for i in range(0, len(a)):
#            for j in range(0, i):
#                if a[j] < a[i]:
#                    d[i] = max(d[i], d[j]+1)
#        for i in range(0, len(d)):
#            n = max(n, d[i])
#        return n

    #
    # O(nlogn) DP plus binary search algo: we allocate
    # an additional array d where we try to collect the
    # sorted entries. To track right position of the array
    # we use pos member. In other words we try to merge entries
    # if their order allows us to.
    #
    # Note though the mapping is surjective thus we loose information
    # which exactly entries are forming the longest subsequence thus
    # if we would need them we are to add another array where we would
    # track parents of entries, that named "parents array".
    def lengthOfLIS(self, a):
        if len(a) < 2:
            return len(a)

        d = [0] * (len(a) + 1)
        d[1] = a[0]
        pos = 1

        for i in range(1, len(a)):
            j = bisect.bisect_right(d, a[i], 1, pos+1)
            if j == pos+1:
                if a[i] != d[j-1]: # eliminate duplicates
                    d[j] = a[i]
                    pos += 1
            else:
                if d[j-1] < a[i] and a[i] < d[j]:
                    d[j] = a[i]
        return pos

data = [
    [10,9,2,5,3,7,101,18],  # => 4 [2,3,7,101]
    [10,9,2,5,3,4],         # => 3 [2,3,4]
    [1,3,6,7,9,4,10,5,6],   # => 6
    [2,2],                  # => 1
]

for i in range(0, len(data)):
    print(Solution().lengthOfLIS(data[i]))
