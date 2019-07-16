from heapq import heappush, heappop

class Solution(object):
    def smallestRange(self, nums):
        maxv = -10**6
        minv = 10**6
        heap = []
        res = [-10**6, 10**6]

        next_pos = 0
        for k in range(0, len(nums)):
            maxv = max(maxv, nums[k][next_pos])
            # push first elem of every array,
            # and remember the array index and
            # next position to fetch.
            heappush(heap, (nums[k][next_pos], k, next_pos+1))

        while heap:
            minv, k, next_pos = heappop(heap)
            size = maxv - minv
            if res[1] - res[0] > size:
                res[0], res[1] = minv, maxv

            #
            # Nothing left
            if next_pos >= len(nums[k]):
                break

            #
            # Fetch the next element from the
            # array minimal value has been taken
            # from. It can't be less than current
            # minimum, since arrays are sorted but
            # may be new maximum.
            elem = nums[k][next_pos]
            maxv = max(maxv, elem)
            heappush(heap, (elem, k, next_pos+1))

        return res

data = [
    [[4, 10, 15, 24, 26],
     [0,  9, 12, 20],
     [5, 18, 22, 30]],         #-> [20, 24]

    [[44754,66821,67697,67705,67745,67866,67890,67891,67893],
     [30112,56984,63713,65107,65868,68327,68422,68452],
     [-20989,-7893,21756,21919,21952,22027,22029,22103,22104,22131,22146],
     [-64491,3262,52473,65208,81359,81389,92554,93811,94311,94354,94414,94458,94496,94496,94504,94516,94529,94529,94530],
     [75112,87519,88776,91285,91338,91354,91360,91380,91381,91383],
     [23093,58724,69961,76713,76908,80636,80727,83412,83894,84190,84272,84360,84466,84468,84470,84474],
     [24985,31617,33069,46221,58104,58140,58200,58268,58305,58329,58357,58358,58396,58407,58410,58411,58413]],
    # -> [22146, 75112]

]
for i in range(0, len(data)):
    print(Solution().smallestRange(data[i]))
