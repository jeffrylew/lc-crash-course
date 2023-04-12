public void printAllNodes(TreeNode root)
{
    Queue<TreeNode> queue = new LinkedList<>();
    queue.add(root);

    while (!queue.isEmpty())
    {
        int nodesInCurrentLevel = queue.size();
        
        // Do some logic here for the current level

        for (int i = 0; i < nodesInCurrentLevel; i++)
        {
            TreeNode node = queue.remove();

            // Do some logic here on the current node
            System.out.println(node.val);

            // Put the next level onto the queue
            if (node.left != null)
            {
                queue.add(node.left);
            }

            if (node.right != null)
            {
                queue.add(node.right);
            }
        }
    }
}