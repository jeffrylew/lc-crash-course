def postorder_dfs(node):
    if not node:
        return
    
    postorder_dfs(node.left)
    postorder_dfs(node.right)
    print(node.val)