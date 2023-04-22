public List<List<Integer>> zigzagLevelOrderBFS(TreeNode root)
{
    if (root == null)
    {
        return new ArrayList<List<Integer>>();
    }

    List<List<Integer>> results = new ArrayList<List<Integer>>();

    // Add root element with delimiter to kick off the BFS loop
    LinkedList<TreeNode> node_queue = new LinkedList<TreeNode>();
    node_queue.addLast(root);
    node_queue.addLast(null);

    LinkedList<Integer> level_list = new LinkedList<Integer>();
    boolean is_order_left = true;

    while (!node_queue.isEmpty())
    {
        TreeNode curr_node = node_queue.pollFirst();
        if (curr_node != null)
        {
            if (is_order_left)
            {
                level_list.addLast(curr_node.val);
            }
            else
            {
                level_list.addFirst(curr_node.val);
            }

            if (curr_node.left != null)
            {
                node_queue.addLast(curr_node.left);
            }

            if (curr_node.right != null)
            {
                node_queue.addLast(curr_node.right);
            }
        }
        else
        {
            // We finish the scan of one level
            results.add(level_list);
            level_list = new LinkedList<Integer>();

            // Prepare for the next level
            if (!node_queue.isEmpty())
            {
                node_queue.addLast(null);
            }

            is_order_left = !is_order_left;
        }
    }

    return results;
}