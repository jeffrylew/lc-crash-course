public int longestOnes(int[] nums, int k)
{
    int left = 0;
    int right;

    for (right = 0; right < nums.length; right++)
    {
        //! If included a zero in the window then reduce value of k
        //! k is the maximum zeros allowed in a window
        if (nums[right] == 0)
        {
            k--;
        }

        //! Negative k denotes have comnsumed all allowed flips and window has
        //! more than allowed zeros, thus increment left pointer by 1 to keep
        //! window size same
        if (k < 0)
        {
            //! If left element to be thrown out is zero then increase k
            if (nums[left] == 0)
            {
                k++;
            }
            left++;
        }
    }

    return right - left;
}