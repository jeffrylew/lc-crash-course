#include <gtest/gtest.h>

#include <vector>

//! @brief Find single element that doesn't appear twice
//! @param[in] nums Non-empty vector of integers
//! @return Single element that doesn't appear twice
static int singleNumber(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/single-number/
    //!
    //!          Time complexity O(N) where N = nums.size()
    //!          Space complexity O(1)

    int mask {};

    for (const int num : nums)
    {
        mask ^= num;
    }

    return mask;
}

TEST(SingleNumberTest, SampleTest1)
{
    EXPECT_EQ(1, singleNumber({2, 2, 1}));
}

TEST(SingleNumberTest, SampleTest2)
{
    EXPECT_EQ(4, singleNumber({4, 1, 2, 1, 2}));
}

TEST(SingleNumberTest, SampleTest3)
{
    EXPECT_EQ(1, singleNumber({1}));
}
