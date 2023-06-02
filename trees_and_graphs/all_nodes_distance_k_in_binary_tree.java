class Solution
{
    Map<TreeNode, TreeNode> parents = new HashMap<>();

    public void dfs(TreeNode node, TreeNode parent)
    {
        if (node == null)
        {
            return;
        }

        parents.put(node, parent);
        dfs(node.left, node);
        dfs(node.right, node);
    }

    public List<Integer> distanceK(TreeNode root, TreeNode target, int k)
    {
        dfs(root, null);

        Queue<TreeNode> queue = new LinkedList<>();
        Set<TreeNode> seen = new HashSet<>();
        queue.add(target);
        seen.add(target);

        int distance = 0;
        while (!queue.isEmpty() && distance < k)
        {
            int currentLength = queue.size();
            for (int i = 0; i < currentLength; i++)
            {
                TreeNode node = queue.remove();
                for (TreeNode neighbor : new TreeNode[]{
                    node.left, node.right, parents.get(node)})
                {
                    if (neighbor != null && !seen.contains(neighbor))
                    {
                        seen.add(neighbor);
                        queue.add(neighbor);
                    }
                }
            }

            distance++;
        }

        List<Integer> ans = new ArrayList<>();
        for (TreeNode node : queue)
        {
            ans.add(node.val);
        }

        return ans;
    }
}