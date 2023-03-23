def dfs(node):
    if node == None:
        return
    
    dfs(node.left)
    dfs(node.right)