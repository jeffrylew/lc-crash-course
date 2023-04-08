import treenode

class Solution:
    def maxAncestorDiff1(self, root: treenode.TreeNode) -> int:
        if not root:
            return 0
        
        # Record the required max difference
        self.result = 0

        def helper(node, cur_max, cur_min):
            if not node:
                return
            
            # Update result
            self.result = max(self.result,
                              abs(cur_max - node.val),
                              abs(cur_min - node.val))
            
            # Update the max and min
            cur_max = max(cur_max, node.val)
            cur_min = min(cur_min, node.val)

            helper(node.left, cur_max, cur_min)
            helper(node.right, cur_max, cur_min)

        helper(root, root.val, root.val)
        return self.result
    
    def maxAncestorDiff2(self, root: treenode.TreeNode) -> int:
        if not root:
            return 0
        
        def helper(node, cur_max, cur_min):
            # If encounter a leaf return max - min along the path
            if not node:
                return cur_max - cur_min
            
            # Else update max and min and return max of left and right subtrees
            cur_max = max(cur_max, node.val)
            cur_min = min(cur_min, node.val)

            left = helper(node.left, cur_max, cur_min)
            right = helper(node.right, cur_max, cur_min)
            return max(left, right)
        
        return helper(root, root.val, root.val)