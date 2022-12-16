public int[] sortedSquaresDS1(int[] nums)
{
    //! @details In Java, Arrays.sort() is implemented as quicksort variant
    //!          whose space complexity is O(log N)
    //!
    //!          Time complexity O(N log N)
    //!          Space complexity O(log N) if output array is ignored

    int   N   = nums.length;
    int[] ans = new int[N];

    for (int i = 0; i < N; ++i)
        ans[i] = nums[i] * nums[i];
    
    Arrays.sort(ans);
    return ans;
}

public int[] sortedSquaresDS2(int[] nums)
{
    int   N   = nums.length;
    int[] ans = new int[N];

    int left  = 0;
    int right = N - 1;

    for (int i = N - 1; i >= 0; --i)
    {
        int square;
        if (Math.abs(nums[left]) < Math.abs(nums[right]))
        {
            square = nums[right--];
        }
        else
        {
            square = nums[left++];
        }
        ans[i] = square * square;
    }

    return ans;
}