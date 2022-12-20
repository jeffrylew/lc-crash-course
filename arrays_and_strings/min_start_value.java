public int minStartValue(int[] nums)
{
    int minVal = 0;
    int total = 0;

    for (int num : nums)
    {
        total += num;
        minVal = Math.min(minVal, total);
    }

    return 1 - min_val;
}