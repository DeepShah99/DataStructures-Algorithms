class Solution(object):
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        val = nums[0]
        for i in range(0, len(nums) - 1):
            val = val ^ nums[i + 1]
        
        return val
