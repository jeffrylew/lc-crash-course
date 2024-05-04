public int singleNumber(int[] nums)
{
    int mask = 0;
    for (int num : nums)
    {
        mask ^= num;
    }

    return mask;
}
