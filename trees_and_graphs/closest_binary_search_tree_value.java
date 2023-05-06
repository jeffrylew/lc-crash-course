class Solution
{
    public void inorder(TreeNode node, List<Integer> nums)
    {
        if (node == null)
        {
            return;
        }

        inorder(node.left, nums);
        nums.add(node.val);
        inorder(node.right, nums);
    }

    public int closestValueRecursive(TreeNode root, double target)
    {
        List<Integer> nums = new ArrayList<>();
        inorder(root, nums);

        return Collections.min(nums, new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2)
            {
                return Math.abs(o1 - target) < Math.abs(o2 - target) ? -1 : 1;
            }
        });
    }

    public int closestValueIterative(TreeNode root, double target)
    {
        LinkedList<TreeNode> stack = new LinkedList<>();
        long pred = Long.MIN_VALUE;

        while (!stack.isEmpty() || root != null)
        {
            while (root != null)
            {
                stack.add(root);
                root = root.left;
            }
            root = stack.removeLast();

            if (pred <= target && target < root.val)
            {
                // Editorial is incorrect here. Need to use <= instead of < to
                // get smallest value that is closest to the target.
                // e.g. target = 3.5, BST contains 3 and 4, return 3
                return Math.abs(pred - target) <= Math.abs(root.val - target)
                    ? (int)pred : root.val;
            }

            pred = root.val;
            root = root.right;
        }

        return (int)pred;
    }

    public int closestValueBinarySearch(TreeNode root, double target)
    {
        int val = root.val;
        int closest = root.val;

        while (root != null)
        {
            val = root.val;

            /*
             * Editorial solution does not pass all cases, see modification
             * 
            closest = Math.abs(val - target) <= Math.abs(closest - target)
                ? val : closest;
             */

            double val_diff = Math.abs(val - target);
            double close_diff = Math.abs(closest - target);

            if (val_diff < close_diff)
            {
                closest = val;
            }
            else if (val_diff == close_diff)
            {
                closest = Math.min(val, closest);
            }

            root = target < root.val ? root.left : root.right;
        }

        return closest;
    }
}