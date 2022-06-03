class Solution(object):
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_sum = max_sum = nums[0]
        for n in nums[1: ]:
            total_sum = max(n, n + total_sum)
            max_sum = max(max_sum, total_sum)
        return max_sum
            
        
    
                
        
