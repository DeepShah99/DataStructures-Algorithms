# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        if root == None:
            return True
        
        return self.check(root.left, root.right)
    
    def check(self, leftroot, rightroot):
        if (leftroot == None and rightroot == None):
            return True
        elif (leftroot and rightroot):
            return leftroot.val == rightroot.val and self.check(leftroot.left, rightroot.right) and self.check(leftroot.right,rightroot.left)
