def inorder_dfs(node):
    if not node:
        return
    
    inorder_dfs(node.left)
    print(node.val)
    inorder_dfs(node.right)