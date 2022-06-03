class Solution(object):
    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
        hash = {1: 1, 2: 2, 3: 3}
        for i in range(4, n + 1):
            hash[i] = hash[i - 1] + hash[i - 2]
        
        return(hash[n])
