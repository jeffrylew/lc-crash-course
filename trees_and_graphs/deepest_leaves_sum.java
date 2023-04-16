public int deepestLeavesSumDFS(TreeNode root)
{
    int deepestSum = 0, depth = 0, currDepth;
    Deque<Pair<TreeNode, Integer>> stack = new ArrayDeque();
    stack.push(new Pair(root, 0));

    while (!stack.isEmpty())
    {
        Pair<TreeNode, Integer> p = stack.pop();
        root = p.getKey();
        currDepth = p.getValue();

        if (root.left == null && root.right == null)
        {
            // If this leaf is the deepest one seen so far
            if (depth < currDepth)
            {
                // Start new sum
                deepestSum = root.val;

                // Note new depth
                depth = currDepth;
            }
            else if (depth == currDepth)
            {
                // If there were already leaves at this depth,
                // update existing sum
                deepestSum += root.val;
            }
        }
        else
        {
            if (root.right != null)
            {
                stack.push(new Pair(root.right, currDepth + 1));
            }

            if (root.left != null)
            {
                stack.push(new Pair(root.left, currDepth + 1));
            }
        }
    }

    return deepestSum;
}

public int deepestLeavesSumBFS(TreeNode root)
{
    ArrayDeque<TreeNode> nextLevel = new ArrayDeque();
    ArrayDeque<TreeNode> currLevel = new ArrayDeque();
    nextLevel.offer(root);

    while (!nextLevel.isEmpty())
    {
        // Prepare for the next level
        currLevel = nextLevel.clone();
        nextLevel.clear();

        for (TreeNode node: currLevel)
        {
            // Add child nodes of the current level
            // in the queue for the next level
            if (node.left != null)
            {
                nextLevel.offer(node.left);
            }

            if (node.right != null)
            {
                nextLevel.offer(node.right);
            }
        }
    }

    int deepestSum = 0;
    for (TreeNode node: currLevel)
    {
        deepestSum += node.val;
    }
    return deepestSum;
}