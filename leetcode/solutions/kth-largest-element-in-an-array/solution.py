class Solution:
    def findKthLargest(self, nums: [int], k: int) -> int:
        if len(nums) == 0:
            return 0
        nums.sort()
        return nums[-k]
