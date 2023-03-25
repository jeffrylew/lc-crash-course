def preorder_dfs(node):
    if not node:
        return
    
    print(node.val)
    preorder_dfs(node.left)
    preorder_dfs(node.right)