public int[] getAveragesDS1(int[] nums, int k)
{
    // When a single element is considered then its average is the num itself
    if (k == 0)
    {
        return nums;
    }

    int windowSize = 2 * k + 1;
    int nums_len = nums.length;
    int[] averages = new int[nums_len];
    Arrays.fill(averages, -1);

    // Case when any index does not have k elements on either side
    if (windowSize > nums_len)
    {
        return averages;
    }

    // Generate prefix array for nums
    // prefix[idx + 1] is the sum of all elements from index 0 to idx
    long[] prefix = new long[nums_len + 1];
    for (int idx = 0; idx < nums_len; ++idx)
    {
        prefix[idx + 1] = prefix[idx] + nums[idx];
    }

    // Only iterate on indices that have at least k elements on either size
    // i.e. Indices from k (inclusive) to nums_len - k (exclusive)
    for (int idx = k; idx < (nums_len - k); ++idx)
    {
        int leftBound = idx - k;
        int rightBound = idx + k;

        long subArraySum = prefix[rightBound + 1] - prefix[leftBound];
        averages[idx] = (int) (subArraySum / windowSize);
    }

    return averages;
}
