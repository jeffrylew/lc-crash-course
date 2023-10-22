#include <gtest/gtest.h>

#include <vector>

//! @brief Split nums into k non-empty subarrays so largest sum is minimized
//! @param[in] nums Vector of ints
//! @param[in] k    Number of non-empty subarrays to split
//! @return Minimized largest sum of the split
static int splitArrayFA(std::vector<int> nums, int k)
{
    //! @todo
}

TEST(SplitArrayTest, SampleTest)
{
    EXPECT_EQ(18, splitArrayFA({7, 2, 5, 10, 8}, 2));

    EXPECT_EQ(9, splitArrayFA({1, 2, 3, 4, 5}, 2));
}