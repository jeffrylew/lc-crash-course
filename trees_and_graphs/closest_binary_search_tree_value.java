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
}