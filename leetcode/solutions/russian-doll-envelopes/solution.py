import bisect

#
# The task is similar to longest-increasing-subsequence
# with one exception: we sort widths in ascending order
# but with heigh in descending order, so the only thing
# left is to find longest height sequence.
class Solution:
    def maxEnvelopes(self, a) -> int:
        if len(a) < 2:
            return len(a)

        a.sort(key=lambda x: (x[0],-x[1]))

        d = [0] * (len(a) + 1)
        d[1] = a[0][1]
        pos = 1

        for i in range(1, len(a)):
            j = bisect.bisect_right(d, a[i][1], 1, pos+1)
            if j == pos+1:
                if a[i][1] != d[j-1]: # eliminate duplicates
                    d[j] = a[i][1]
                    pos += 1
            else:
                if d[j-1] < a[i][1] and a[i][1] < d[j]:
                    d[j] = a[i][1]
        return pos

data = [
    [[2,100],[3,200],[4,300],[5,500],[5,400],[5,250],[6,370],[6,360],[7,380]], # => 5
    [[4,5],[4,6],[6,7],[2,3],[1,1],[1,1]],    # => 4
    [[1,1],[1,1],[1,1]],                    # => 1
    [[4,5],[6,7],[2,3]],                    # => 3
    [[5,4],[6,4],[6,7],[2,3]],              # => 3 [2,3] => [5,4] => [6,7]
]

for i in range(0, len(data)):
    print(Solution().maxEnvelopes(data[i]))
