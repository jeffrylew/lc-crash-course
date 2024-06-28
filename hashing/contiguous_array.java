public int findMaxLengthDS1(int[] nums)
{
    int max_len = 0;

    for (int start = 0; start < nums.length; start++)
    {
        int zeros = 0;
        int ones = 0;

        for (int end = start; end < nums.length; end++)
        {
            if (nums[end] == 0)
            {
                zeros++;
            }
            else
            {
                ones++;
            }

            if (zeros == ones)
            {
                max_len = Math.max(max_len, end - start + 1);
            }
        }
    }

    return max_len;
}
