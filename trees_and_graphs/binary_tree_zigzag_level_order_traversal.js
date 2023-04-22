/**
 * @param {TreeNode} root
 * @return {number[][]}
 */
var zigzagLevelOrderBFS = function(root)
{
    if (!root)
    {
        return [];
    }

    let results = [];

    // Add the root element with a delimiter to kick off the BFS loop
    let node_queue = [root, null];

    let level_list = [];
    let is_order_left = true;

    while (node_queue.length)
    {
        const curr_node = node_queue.shift();
        if (curr_node != null)
        {
            if (is_order_left)
            {
                level_list.push(curr_node.val);
            }
            else
            {
                level_list.unshift(curr_node.val);
            }

            if (curr_node.left)
            {
                node_queue.push(curr_node.left);
            }

            if (curr_node.right)
            {
                node_queue.push(curr_node.right);
            }
        }
        else
        {
            // We finish the scan of one level
            results.push(level_list);
            level_list = [];

            // Prepare for the next level
            if (node_queue.length)
            {
                node_queue.push(null);
            }

            is_order_left = !is_order_left;
        }
    }

    return results;
};

var DFS_helper = function(node, level, results)
{
    if (level >= results.length)
    {
        results.push([node.val]);
    }
    else
    {
        if (level % 2 == 0)
        {
            results[level].push(node.val);
        }
        else
        {
            results[level].unshift(node.val);
        }
    }

    if (node.left)
    {
        DFS_helper(node.left, level + 1, results);
    }

    if (node.right)
    {
        DFS_helper(node.right, level + 1, results);
    }
}

/**
 * @param {TreeNode} root
 * @return {number[][]}
 */
var zigzagLevelOrderDFS = function(root)
{
    if (!root)
    {
        return [];
    }

    let results = [];
    DFS_helper(root, 0, results);
    return results;
};