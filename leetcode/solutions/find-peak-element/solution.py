class Solution:
    def findPeakElement(self, a) -> int:
        if len(a) < 2:
            return len(a)-1

        idx = None
        for i in range(1, len(a)-1):
            if a[i] > a[i-1] and a[i] > a[i+1]:
                idx = i
                break
        if idx == None:
            if a[0] > a[1]:
                idx = 0
            elif a[len(a)-1] > a[len(a)-2]:
                idx = len(a)-1
        return idx

data = [
    [1,2,3,1],          # => 2
    [1,2,1,3,5,6,4],    # => 1 or 5
]
for i in range(0, len(data)):
    print(Solution().findPeakElement(data[i]))
