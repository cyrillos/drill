class Solution:
    #
    # The idea is simple -- every rectangle area from
    # two elements of array is bound by minimal height,
    # the only thing we should do is to start from array
    # left and right border and calculate the area of
    # the current rectangle. Next one we choose is with
    # minimal height.
    def maxArea(self, a) -> int:
        area = 0
        l, r = 0, len(a)-1
        while l < r:
            area = max(area, min(a[l], a[r]) * (r-l))
            if a[l] < a[r]:
                l+=1
            else:
                r-=1
        return area

data = [
    [1, 8, 6, 2, 5, 4, 8, 3, 7],
]
for i in range(0, len(data)):
    print(Solution().maxArea(data[i]))
