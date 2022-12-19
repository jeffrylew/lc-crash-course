#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Maximum number of consecutive 1s if can flip at most k 0s
//! @param[in] nums Vector of binary integers
//! @param[in] k    Max number of 0s that can be flipped
//! @return Max number of consecutive 1s in vector if can flip at most k 0s
static int longestOnesFA(std::vector<int> nums, int k)
{
    int curr_zeros {};
    int max_ones {};
    int left {};

    for (int right = 0; right < static_cast<int>(nums.size()); ++right)
    {
        if (nums[right] == 0)
        {
            ++curr_zeros;
        }
        
        while (curr_zeros > k)
        {
            if (nums[left++] == 0)
            {
                --curr_zeros;
            }
        }
        
        max_ones = std::max(max_ones, right - left + 1);
    }

    return max_ones;

} // static int longestOnesFA( ...

//! @brief Discussion solution
//! @param[in] nums Vector of binary integers
//! @param[in] k    Max number of 0s that can be flipped
//! @return Max number of consecutive 1s in vector if can flip at most k 0s
static int longestOnesDS(std::vector<int> nums, int k)
{
    //! @details Time complexity O(N) where N = nums.size(). In worst case, may
    //!          visit every element of nums twice, once by left pointer and
    //!          once by right pointer.
    //!          Space complexity O(1)

    int left {};
    int right;

    for (right = 0; right < static_cast<int>(nums.size()); ++right)
    {
        //! If include a zero in the window, reduce the value of k
        //! k is the maximum zeros allowed in a window
        if (nums[right] == 0)
        {
            --k;
        }
        
        //! Negative k denotes have consumed all allowed flips and window has
        //! more than allowed zeros, Thus increment left pointer by 1 to keep
        //! window size same
        if (k < 0)
        {
            //! If left element to be thrown out is zero, increase k
            if (nums[left] == 0)
            {
                ++k;
            }
            ++left;
        }
    }

    return right - left;

} // static int longestOnesDS( ...

TEST(LongestOnesTest, SampleTest)
{
    EXPECT_EQ(6, longestOnesFA({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2));
    EXPECT_EQ(6, longestOnesDS({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2));
}