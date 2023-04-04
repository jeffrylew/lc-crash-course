public int minDepthRecursive(TreeNode root)
{
    if (root == null)
    {
        return 0;
    }

    if (root.left == null && root.right == null)
    {
        return 1;
    }

    int min_depth = Integer.MAX_VALUE;
    if (root.left != null)
    {
        min_depth = Math.min(minDepthRecursive(root.left), min_depth);
    }

    if (root.right != null)
    {
        min_depth = Math.min(minDepthRecursive(root.right), min_depth);
    }

    return min_depth + 1;
}

class Pair
{
    TreeNode node;
    int depth;

    Pair(TreeNode node, int depth)
    {
        this.node = node;
        this.depth = depth;
    }
}

public int minDepthDFSIterative(TreeNode root)
{
    if (root == null)
    {
        return 0;
    }

    Stack<Pair> stack = new Stack<>();
    stack.push(new Pair(root, 1));

    int min_depth = Integer.MAX_VALUE;
    while (!stack.empty())
    {
        Pair current = stack.pop();
        TreeNode node = current.node;
        int current_depth = current.depth;

        if (node.left == null && node.right == null)
        {
            min_depth = Math.min(min_depth, current_depth);
        }

        if (node.left != null)
        {
            stack.push(new Pair(node.left, current_depth + 1));
        }

        if (node.right != null)
        {
            stack.push(new Pair(node.right, current_depth + 1));
        }
    }

    return min_depth;
}

public int minDepthBFSIterative(TreeNode root)
{
    if (root == null)
    {
        return 0;
    }

    Queue<Pair> queue = new LinkedList<>();
    queue.offer(new Pair(root, 1));

    int current_depth = 0;
    while (!queue.isEmpty())
    {
        Pair pair = queue.poll();
        TreeNode node = pair.node;
        current_depth = pair.depth;

        if (node.left == null && node.right == null)
        {
            break;
        }

        if (node.left != null)
        {
            queue.offer(new Pair(node.left, current_depth + 1));
        }

        if (node.right != null)
        {
            queue.offer(new Pair(node.right, current_depth + 1));
        }
    }
    
    return current_depth;
}