# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        return self.height(root)  
    def height(self, root):
        if root == None:
            return 0
            
        l = self.height(root.left)
        r = self.height(root.right)
            
        if(l > r):
            h = l + 1
        else:
            h = r + 1
        return h
