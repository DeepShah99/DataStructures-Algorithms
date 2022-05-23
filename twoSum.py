class Solution(object):
    def twoSum(self, nums, target):
              hash = {} # number->key : index->pair
            
              for count, number in enumerate(nums):
                diff = target - number
                if diff in hash:
                    return (hash[diff], count)
                hash[number] = count
              
            
       
      
    
            
