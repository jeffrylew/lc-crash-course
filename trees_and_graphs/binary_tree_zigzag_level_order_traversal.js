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