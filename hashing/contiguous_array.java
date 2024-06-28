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

public int findMaxLengthDS3(int[] nums)
{
    Map<Integer, Integer> count_idx = new HashMap<>();
    count_idx.put(0, 1);

    int max_len = 0;
    int count = 0;

    for (int idx = 0; idx < nums.length; idx++)
    {
        count = count + (nums[idx] == 0 ? -1 : 1);

        if (count_idx.containsKey(count))
        {
            max_len = Math.max(max_len, idx - count_idx.get(count));
        }
        else
        {
            count_idx.put(count, idx);
        }
    }

    return max_len;
}
